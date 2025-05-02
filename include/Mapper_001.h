#pragma once
#include "Mapper.h"
#include <vector>

class Mapper_001 : public Mapper
{
public:
	Mapper_001(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_001();

public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data) override;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) override;
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;

	void reset() override;
    MIRROR mirror();

private:
	uint8_t m_nCHRBankSelect4Lo = 0x00;
	uint8_t m_nCHRBankSelect4Hi = 0x00;
	uint8_t m_nCHRBankSelect8 = 0x00;

	uint8_t m_nPRGBankSelect16Lo = 0x00;
	uint8_t m_nPRGBankSelect16Hi = 0x00;
	uint8_t m_nPRGBankSelect32 = 0x00;
    
	uint8_t m_nLoadRegister = 0x00;
	uint8_t m_nLoadRegisterCount = 0x00;
	uint8_t m_nControlRegister = 0x00;

    MIRROR mirrormode = MIRROR::HORIZONTAL;

    std::vector<uint8_t> m_vRAMStatic;
};