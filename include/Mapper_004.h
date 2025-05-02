#pragma once
#include "Mapper.h"
#include <vector>

class Mapper_004 : public Mapper
{
public:
	Mapper_004(uint8_t prgBanks, uint8_t chrBanks);
	~Mapper_004();

public:
	virtual bool cpuMapRead(uint16_t addr, uint32_t &mapped_addr, uint8_t &data) override;
	virtual bool cpuMapWrite(uint16_t addr, uint32_t &mapped_addr, uint8_t data = 0) override;
	virtual bool ppuMapRead(uint16_t addr, uint32_t &mapped_addr) override;
	virtual bool ppuMapWrite(uint16_t addr, uint32_t &mapped_addr) override;

	void reset() override;

    bool irqState() override;
    void irqClear() override;

    void scanline() override;
    MIRROR mirror();

private:
	uint8_t m_nTargetRegister = 0x00;
	bool m_bPRGBankMode = false;
    bool m_bCHRInversion = false;

    MIRROR mirrormode = MIRROR::HORIZONTAL;

	uint32_t m_pRegister[8];
	uint32_t m_pCHRBank[8];
	uint32_t m_pPRGBank[4];

	bool m_bIRQActive = false;
	bool m_bIRQEnable = false;
	bool m_bIRQUpdate = false;
	uint16_t m_nIRQCounter = 0x0000;
	uint16_t m_nIRQReload = 0x0000;

    std::vector<uint8_t> m_vRAMStatic;
};