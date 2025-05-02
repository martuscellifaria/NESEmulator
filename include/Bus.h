#pragma once
#include <array>
#include <cstdint>
#include <memory>

#include "chip6502.h"
#include "chip2C02.h"
#include "chip2A03.h"
#include "Cartridge.h"

class Bus
{
public:
    Bus();
    virtual ~Bus();

public:
    Chip6502 cpu;
    Chip2C02 ppu;
    chip2A03 apu;
    std::shared_ptr<Cartridge> m_pCart;
    uint8_t m_uCpuRam[2048];
    uint8_t m_uController[2];

    double m_dAudioSample = 0.0;

public:
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
    void SetSampleFrequency(u_int32_t sample_rate);

public:
    void insertCartridge(const std::shared_ptr<Cartridge>& pCartridge);
    void reset();
    bool clock();

private:
    double m_dAudioTimePerSystemSample = 0.0f;
    double m_dAudioTimePerNESClock = 0.0f;
    double m_dAudioTime = 0.0f;

    uint32_t m_uNSystemClockCounter = 0;
	uint8_t m_uControllerState[2];

    uint8_t m_uDmaPage = 0x00;
    uint8_t m_uDmaAddr = 0x00;
    uint8_t m_uDmaData = 0x00;

    bool m_bDmaTransfer = false;
    bool m_bDmaDummy = true;
    static constexpr double PPU_CLOCK_FREQUENCY = 5369318.0;
};