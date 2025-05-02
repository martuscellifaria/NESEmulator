#pragma once
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "Mapper_000.h"
#include "Mapper_001.h"
#include "Mapper_002.h"
#include "Mapper_003.h"
#include "Mapper_004.h"
#include "Mapper_066.h"

class Cartridge
{
public:
    Cartridge(const std::string& sFileName);
    ~Cartridge();

public:
	bool imageValid();

private:
    bool bImageValid = false;
    MIRROR hw_mirror = HORIZONTAL;

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

    MIRROR Mirror();
    std::shared_ptr<Mapper> GetMapper() { return m_pMapper; }
};