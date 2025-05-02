#include "Mapper_004.h"

Mapper_004::Mapper_004(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
}


Mapper_004::~Mapper_004()
{
}

bool Mapper_004::cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data)
{
	if (addr >= 0x6000 && addr <= 0x7FFF)
	{
		mapped_addr = 0xFFFFFFFF;
		data = m_vRAMStatic[addr & 0x1FFF];
		return true;
	}


	if (addr >= 0x8000 && addr <= 0x9FFF)
	{
		mapped_addr = m_pPRGBank[0] + (addr & 0x1FFF);
		return true;
	}

	if (addr >= 0xA000 && addr <= 0xBFFF)
	{
		mapped_addr = m_pPRGBank[1] + (addr & 0x1FFF);
		return true;
	}

	if (addr >= 0xC000 && addr <= 0xDFFF)
	{
		mapped_addr = m_pPRGBank[2] + (addr & 0x1FFF);
		return true;
	}

	if (addr >= 0xE000 && addr <= 0xFFFF)
	{
		mapped_addr = m_pPRGBank[3] + (addr & 0x1FFF);
		return true;
	}

	return false;
}

bool Mapper_004::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data)
{
	if (addr >= 0x6000 && addr <= 0x7FFF)
	{
		mapped_addr = 0xFFFFFFFF;
		m_vRAMStatic[addr & 0x1FFF] = data;
		return true;
	}

	if (addr >= 0x8000 && addr <= 0x9FFF)
	{
		if (!(addr & 0x0001))
		{
			m_nTargetRegister = data & 0x07;
			m_bPRGBankMode = (data & 0x40);
			m_bCHRInversion = (data & 0x80);
		}
		else
		{
			m_pRegister[m_nTargetRegister] = data;

			if (m_bCHRInversion)
			{
				m_pCHRBank[0] = m_pRegister[2] * 0x0400;
				m_pCHRBank[1] = m_pRegister[3] * 0x0400;
				m_pCHRBank[2] = m_pRegister[4] * 0x0400;
				m_pCHRBank[3] = m_pRegister[5] * 0x0400;
				m_pCHRBank[4] = (m_pRegister[0] & 0xFE) * 0x0400;
				m_pCHRBank[5] = m_pRegister[0] * 0x0400 + 0x0400;
				m_pCHRBank[6] = (m_pRegister[1] & 0xFE) * 0x0400;
				m_pCHRBank[7] = m_pRegister[1] * 0x0400 + 0x0400;
			}
			else
			{
				m_pCHRBank[0] = (m_pRegister[0] & 0xFE) * 0x0400;
				m_pCHRBank[1] = m_pRegister[0] * 0x0400 + 0x0400;
				m_pCHRBank[2] = (m_pRegister[1] & 0xFE) * 0x0400;
				m_pCHRBank[3] = m_pRegister[1] * 0x0400 + 0x0400;
				m_pCHRBank[4] = m_pRegister[2] * 0x0400;
				m_pCHRBank[5] = m_pRegister[3] * 0x0400;
				m_pCHRBank[6] = m_pRegister[4] * 0x0400;
				m_pCHRBank[7] = m_pRegister[5] * 0x0400;
			}

			if (m_bPRGBankMode)
			{
				m_pPRGBank[2] = (m_pRegister[6] & 0x3F) * 0x2000;
				m_pPRGBank[0] = (m_nPRGBanks * 2 - 2) * 0x2000;
			}
			else
			{
				m_pPRGBank[0] = (m_pRegister[6] & 0x3F) * 0x2000;
				m_pPRGBank[2] = (m_nPRGBanks * 2 - 2) * 0x2000;
			}

			m_pPRGBank[1] = (m_pRegister[7] & 0x3F) * 0x2000;
			m_pPRGBank[3] = (m_nPRGBanks * 2 - 1) * 0x2000;

		}

		return false;
	}

	if (addr >= 0xA000 && addr <= 0xBFFF)
	{
		if (!(addr & 0x0001))
		{
			if (data & 0x01)
				mirrormode = MIRROR::HORIZONTAL;
			else
				mirrormode = MIRROR::VERTICAL;
		}
		else
		{
		}
		return false;
	}

	if (addr >= 0xC000 && addr <= 0xDFFF)
	{
		if (!(addr & 0x0001))
		{
			m_nIRQReload = data;
		}
		else
		{
			m_nIRQCounter = 0x0000;
		}
		return false;
	}

	if (addr >= 0xE000 && addr <= 0xFFFF)
	{
		if (!(addr & 0x0001))
		{
			m_bIRQEnable = false;
			m_bIRQActive = false;
		}
		else
		{
			m_bIRQEnable = true;
		}
		return false;
	}
	return false;
}

bool Mapper_004::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr >= 0x0000 && addr <= 0x03FF)
	{
		mapped_addr = m_pCHRBank[0] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x0400 && addr <= 0x07FF)
	{
		mapped_addr = m_pCHRBank[1] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x0800 && addr <= 0x0BFF)
	{
		mapped_addr = m_pCHRBank[2] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x0C00 && addr <= 0x0FFF)
	{
		mapped_addr = m_pCHRBank[3] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x1000 && addr <= 0x13FF)
	{
		mapped_addr = m_pCHRBank[4] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x1400 && addr <= 0x17FF)
	{
		mapped_addr = m_pCHRBank[5] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x1800 && addr <= 0x1BFF)
	{
		mapped_addr = m_pCHRBank[6] + (addr & 0x03FF);
		return true;
	}

	if (addr >= 0x1C00 && addr <= 0x1FFF)
	{
		mapped_addr = m_pCHRBank[7] + (addr & 0x03FF);
		return true;
	}

	return false;
}

bool Mapper_004::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
	return false;
}

void Mapper_004::reset()
{
	m_nTargetRegister = 0x00;
	m_bPRGBankMode = false;
	m_bCHRInversion = false;
	mirrormode = MIRROR::HORIZONTAL;

	m_bIRQActive = false;
	m_bIRQEnable = false;
	m_bIRQUpdate = false;
	m_nIRQCounter = 0x0000;
	m_nIRQReload = 0x0000;

    for (int i = 0; i < 8; i++)
    {
        if (i < 4)
        {
            m_pPRGBank[i] = 0;
        }
        m_pCHRBank[i] = 0;
        m_pRegister[i] = 0;
    }

	m_pPRGBank[0] = 0 * 0x2000;
	m_pPRGBank[1] = 1 * 0x2000;
	m_pPRGBank[2] = (m_nPRGBanks * 2 - 2) * 0x2000;
	m_pPRGBank[3] = (m_nPRGBanks * 2 - 1) * 0x2000;
}

bool Mapper_004::irqState()
{
	return m_bIRQActive;
}

void Mapper_004::irqClear()
{
	m_bIRQActive = false;
}

void Mapper_004::scanline()
{
	if (m_nIRQCounter == 0)
	{		
		m_nIRQCounter = m_nIRQReload;
	}
	else
    {
        m_nIRQCounter--;
    }

	if (m_nIRQCounter == 0 && m_bIRQEnable)
	{
		m_bIRQActive = true;
	}
	
}

MIRROR Mapper_004::mirror()
{
    return mirrormode;
}
