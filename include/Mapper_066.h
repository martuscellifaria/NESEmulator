#pragma once
#include "Mapper.h"


class Mapper_066 : public Mapper
{
public:
	Mapper_066(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_066();

public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data) override;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) override;
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;

	void reset() override;

private:
	uint8_t m_nCHRBankSelect = 0x00;
	uint8_t m_nPRGBankSelect = 0x00;
};