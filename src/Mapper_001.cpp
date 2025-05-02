#include "Mapper_001.h"

Mapper_001::Mapper_001(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
	m_vRAMStatic.resize(32 * 1024);
}


Mapper_001::~Mapper_001()
{
}

bool Mapper_001::cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data)
{
	if (addr >= 0x6000 && addr <= 0x7FFF)
	{
        mapped_addr = 0xFFFFFFFF;
        data = m_vRAMStatic[addr & 0x1FFF];
		return true;
	}
    if (addr >= 0x8000)
    {
        if (m_nControlRegister & 0b01000)
        {
            if (addr >= 0x8000 && addr <= 0xBFFF)
            {
                mapped_addr = m_nPRGBankSelect16Lo * 0x4000 + (addr & 0x3FFF);
                return true;
            }
            if (addr >= 0xC000 && addr <= 0xFFFF)
            {
                mapped_addr = m_nPRGBankSelect16Hi * 0x4000 + (addr & 0x3FFF);
                return true;
            }
        }
        else
        {
            mapped_addr = m_nPRGBankSelect32 * 0x8000 + (addr & 0x7FFF);
            return true;
        }
    }

	return false;
}

bool Mapper_001::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data)
{
	if (addr >= 0x6000 && addr <= 0x7FFF)
	{
		mapped_addr = 0xFFFFFFFF;
		m_vRAMStatic[addr & 0x1FFF] = data;
		return true;
	}
    if (addr >= 0x8000)
	{
		if (data & 0x80)
		{
			m_nLoadRegister = 0x00;
			m_nLoadRegisterCount = 0;
			m_nControlRegister = m_nControlRegister | 0x0C;
		}
		else
		{
			m_nLoadRegister >>= 1;
			m_nLoadRegister |= (data & 0x01) << 4;
			m_nLoadRegisterCount++;

			if (m_nLoadRegisterCount == 5)
			{
				uint8_t nTargetRegister = (addr >> 13) & 0x03;

				if (nTargetRegister == 0)
				{
					m_nControlRegister = m_nLoadRegister & 0x1F;

					switch (m_nControlRegister & 0x03)
					{
					case 0:	mirrormode = ONESCREEN_LO; break;
					case 1: mirrormode = ONESCREEN_HI; break;
					case 2: mirrormode = VERTICAL;     break;
					case 3:	mirrormode = HORIZONTAL;   break;
					}
				}
				else if (nTargetRegister == 1)
				{
					if (m_nControlRegister & 0b10000) 
					{
						m_nCHRBankSelect4Lo = m_nLoadRegister & 0x1F;
					}
					else
					{
						m_nCHRBankSelect8 = m_nLoadRegister & 0x1E;
					}
				}
				else if (nTargetRegister == 2)
				{
					if (m_nControlRegister & 0b10000)
					{
						m_nCHRBankSelect4Hi = m_nLoadRegister & 0x1F;
					}
				}
				else if (nTargetRegister == 3)
				{
					uint8_t nPRGMode = (m_nControlRegister >> 2) & 0x03;

					if (nPRGMode == 0 || nPRGMode == 1)
					{
						m_nPRGBankSelect32 = (m_nLoadRegister & 0x0E) >> 1;
					}
					else if (nPRGMode == 2)
					{
						m_nPRGBankSelect16Lo = 0;
						m_nPRGBankSelect16Hi = m_nLoadRegister & 0x0F;
					}
					else if (nPRGMode == 3)
					{
						m_nPRGBankSelect16Lo = m_nLoadRegister & 0x0F;
						m_nPRGBankSelect16Hi = m_nPRGBanks - 1;
					}
				}
				m_nLoadRegister = 0x00;
				m_nLoadRegisterCount = 0;
			}

		}

	}
	return false;
}

bool Mapper_001::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr < 0x2000)
	{
		if (m_nCHRBanks == 0)
		{
			mapped_addr = addr;
			return true;
		}
		else
		{
			if (m_nControlRegister & 0b10000)
			{
				if (addr >= 0x0000 && addr <= 0x0FFF)
				{
					mapped_addr = m_nCHRBankSelect4Lo * 0x1000 + (addr & 0x0FFF);
					return true;
				}

				if (addr >= 0x1000 && addr <= 0x1FFF)
				{
					mapped_addr = m_nCHRBankSelect4Hi * 0x1000 + (addr & 0x0FFF);
					return true;
				}
			}
			else
			{
				mapped_addr = m_nCHRBankSelect8 * 0x2000 + (addr & 0x1FFF);
				return true;
			}
		}
	}

	return false;
}

bool Mapper_001::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
{
    if (addr < 0x2000)
    {
        if (m_nCHRBanks == 0)
        {
            mapped_addr = addr;
        }
        return true;
    }
	return false;
}

void Mapper_001::reset()
{
	m_nCHRBankSelect4Lo = 0;
	m_nCHRBankSelect4Hi = 0;
	m_nCHRBankSelect8 = 0;

	m_nPRGBankSelect16Lo = 0;
	m_nPRGBankSelect16Hi = m_nPRGBanks -1;
	m_nPRGBankSelect32 = 0;
    
	m_nLoadRegister = 0x00;
	m_nLoadRegisterCount = 0x00;
	m_nControlRegister = 0x1C;
}

MIRROR Mapper_001::mirror()
{
    return mirrormode;
}
