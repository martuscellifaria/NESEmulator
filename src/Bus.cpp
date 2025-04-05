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
        cpuRam[addr & 0x07FF] = data;
    }
	else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
		ppu.cpuWrite(addr & 0x0007, data);
    }
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		controller_state[addr & 0x0001] = controller[addr & 0x0001];
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
		data = cpuRam[addr & 0x07FF];
	}
	else if (addr >= 0x2000 && addr <= 0x3FFF)
	{
		data = ppu.cpuRead(addr & 0x0007, bReadOnly);
	}
	else if (addr >= 0x4016 && addr <= 0x4017)
	{
		data = (controller_state[addr & 0x0001] & 0x80) > 0;
		controller_state[addr & 0x0001] <<= 1;
	}

	return data;
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

void Bus::clock()
{
	ppu.clock();
	if (m_uNSystemClockCounter % 3 == 0)
	{
		cpu.clock();
	}

    if (ppu.m_bNmi)
    {
        ppu.m_bNmi = false;
        cpu.nmi();
    }

	m_uNSystemClockCounter++;
}