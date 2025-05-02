#include "Mapper_002.h"

Mapper_002::Mapper_002(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks)
{
}


Mapper_002::~Mapper_002()
{
}

bool Mapper_002::cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data)
{
	if (addr >= 0x8000 && addr <= 0xBFFF)
	{
		mapped_addr = m_nPRGBankSelectLo * 0x4000 + (addr & 0x3FFF);
		return true;
	}

	if (addr >= 0xC000 && addr <= 0xFFFF)
	{
		mapped_addr = m_nPRGBankSelectHi * 0x4000 + (addr & 0x3FFF);
		return true;
	}

	return false;
}

bool Mapper_002::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data)
{
	if (addr >= 0x8000 && addr <= 0xFFFF)
	{
		m_nPRGBankSelectLo = data & 0x0F;
	}

	return false;
}

bool Mapper_002::ppuMapRead(uint16_t addr, uint32_t &mapped_addr)
{
	if (addr < 0x2000)
	{
		mapped_addr = addr;
		return true;
	}

	return false;
}

bool Mapper_002::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr)
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

void Mapper_002::reset()
{
	m_nPRGBankSelectLo = 0;
	m_nPRGBankSelectHi = m_nPRGBanks - 1;
}
