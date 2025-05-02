#pragma once
#include "Mapper.h"


class Mapper_003 : public Mapper
{
public:
	Mapper_003(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_003();

public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data) override;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) override;
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;

	void reset() override;

private:
	uint8_t m_nPRGBankSelect = 0x00;
};