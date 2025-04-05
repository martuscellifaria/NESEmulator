#pragma once
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "Mapper_000.h"

class Cartridge
{
public:
    Cartridge(const std::string& sFileName);
    ~Cartridge();

public:
	bool ImageValid();

	enum MIRROR
	{
		HORIZONTAL,
		VERTICAL,
		ONESCREEN_LO,
		ONESCREEN_HI,
	} mirror = HORIZONTAL;

private:
    bool bImageValid = false;

    uint8_t m_nMapperID = 0;
    uint8_t m_nPRGBanks = 0;
    uint8_t m_nCHRBanks = 0;

    std::vector<uint8_t> m_vPRGMemory;
    std::vector<uint8_t> m_vCHRMemory;
    
    std::shared_ptr<Mapper> m_pMapper;

public:
    bool cpuRead(uint16_t addr, uint8_t& data);
    bool cpuWrite(uint16_t addr, uint8_t data);

    bool ppuRead(uint16_t addr,  uint8_t& data);
    bool ppuWrite(uint16_t addr, uint8_t data);

    void reset();
};