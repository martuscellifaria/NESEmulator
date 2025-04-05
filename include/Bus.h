#pragma once
#include <array>
#include <cstdint>
#include <memory>

#include "chip6502.h"
#include "chip2C02.h"
#include "Cartridge.h"

class Bus
{
public:
    Bus();
    virtual ~Bus();

public:
    Chip6502 cpu;
    Chip2C02 ppu;
    std::shared_ptr<Cartridge> m_pCart;
    uint8_t cpuRam[2048];
    uint8_t controller[2];

public:
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);

private:
    uint32_t m_uNSystemClockCounter = 0;
	uint8_t controller_state[2];

public:
    void insertCartridge(const std::shared_ptr<Cartridge>& pCartridge);
    void reset();
    void clock();

public:
    static uint16_t constexpr CPU_LOWER_BOUND = 0x0000;
    static uint16_t constexpr CPU_UPPER_BOUND = 0x1FFF;
    static uint16_t constexpr PPU_LOWER_BOUND = 0x2000;
    static uint16_t constexpr PPU_UPPER_BOUND = 0x3FFF;
    static uint16_t constexpr MIRRORING = 0x07FF;
    static uint16_t constexpr PPU_REFERENCE = 0x0007;
};