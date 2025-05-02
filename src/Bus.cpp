#include "Bus.h"

Bus::Bus()
{
    cpu.connectBus(this);
}

Bus::~Bus()
{
    
}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (m_pCart->cpuWrite(addr, data))
    {
    }
	else if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        m_uCpuRam[addr & 0x07FF] = data;
    }
	else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
		ppu.cpuWrite(addr & 0x0007, data);
    }
	else if ((addr >= 0x4000 && addr <= 0x4013 || addr == 0x4015 || addr == 0x4017))
	{
		apu.cpuWrite(addr, data);
	}
	else if (addr == 0x4014)
	{
		m_uDmaPage = data;
		m_uDmaAddr= 0x00;
		m_bDmaTransfer = true;
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		m_uControllerState[addr & 0x0001] = m_uController[addr & 0x0001];
	}
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly)
{
    uint8_t data = 0x00;	
	if (m_pCart->cpuRead(addr, data))
	{
	}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		data = m_uCpuRam[addr & 0x07FF];
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		data = ppu.cpuRead(addr & 0x0007, bReadOnly);
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		data = (m_uControllerState[addr & 0x0001] & 0x80) > 0;
		m_uControllerState[addr & 0x0001] <<= 1;
	}

	return data;
}

void Bus::SetSampleFrequency(u_int32_t sample_rate)
{
	m_dAudioTimePerSystemSample = 1.0/(double)sample_rate;
	m_dAudioTimePerNESClock = 1.0/PPU_CLOCK_FREQUENCY;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& pCartridge)
{
    this->m_pCart = pCartridge;
    ppu.ConnectCartridge(pCartridge);
}

void Bus::reset()
{
    m_pCart->reset();
	cpu.reset();
	ppu.reset();
	m_uNSystemClockCounter = 0;
}

bool Bus::clock()
{
	ppu.clock();
	apu.clock();
	if (m_uNSystemClockCounter % 3 == 0)
	{
		if (m_bDmaTransfer)
		{
			if (m_bDmaDummy)
			{
				if (m_uNSystemClockCounter %2 == 1)
				{
					m_bDmaDummy = false;
				}
			}
			else
			{
				if (m_uNSystemClockCounter %2 == 0)
				{
					m_uDmaData = cpuRead(m_uDmaPage << 8 | m_uDmaAddr);
				}
				else
				{
					ppu.m_pOAM[m_uDmaAddr] = m_uDmaData;
					m_uDmaAddr++;

					if (m_uDmaAddr == 0x00)
					{
						m_bDmaTransfer = false;
						m_bDmaDummy = true;
					}
				}
			}
		}
		else
		{
			cpu.clock();
		}
	}

	bool bAudioSampleReady = false;
	m_dAudioTime += m_dAudioTimePerNESClock;
	if (m_dAudioTime >= m_dAudioTimePerSystemSample)
	{
		m_dAudioTime -= m_dAudioTimePerSystemSample;
		m_dAudioSample = apu.GetOutputSample();
		bAudioSampleReady = true;
	}

    if (ppu.m_bNmi)
    {
        ppu.m_bNmi = false;
        cpu.nmi();
    }

	if (m_pCart->GetMapper()->irqState())
	{
		m_pCart->GetMapper()->irqClear();
		cpu.irq();
	}

	m_uNSystemClockCounter++;

	return bAudioSampleReady;
}