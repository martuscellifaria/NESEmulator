#pragma once
#include <cstdint>
#include <memory>
#include "olcPixelGameEngine.h"
#include "Cartridge.h"

class Chip2C02
{
public:
    Chip2C02();
    virtual ~Chip2C02();

public:
    uint8_t m_uTableName[2][1024];
    uint8_t m_uTablePattern[2][4096];
    uint8_t m_uTablePalette[32];

private:
        olc::Pixel m_pPalScreen[0x40];
        olc::Sprite* m_sSprScreen;
        olc::Sprite* m_sSprNameTable[2];
        olc::Sprite* m_sSprPatternTable[2];

public:
        // Debugging Utilities
        olc::Sprite& GetScreen();
        olc::Sprite& GetNameTable(uint8_t i);
        olc::Sprite& GetPatternTable(uint8_t i, uint8_t palette);

        olc::Pixel& GetColourFromPaletteRam(uint8_t palette, uint8_t pixel);
        bool m_bFrameComplete = false;

private:

    union
    {
        struct
        {
            uint8_t unused : 5;
            uint8_t sprite_overflow : 1;
            uint8_t sprite_zero_hit : 1;
            uint8_t vertical_blank : 1;
        };

        uint8_t reg;
    } status;

	union
	{
		struct
		{
			uint8_t grayscale : 1;
			uint8_t render_background_left : 1;
			uint8_t render_sprites_left : 1;
			uint8_t render_background : 1;
			uint8_t render_sprites : 1;
			uint8_t enhance_red : 1;
			uint8_t enhance_green : 1;
			uint8_t enhance_blue : 1;
		};
		uint8_t reg;
	} mask;

	union PPUCTRL
	{
		struct
		{
			uint8_t nametable_x : 1;
			uint8_t nametable_y : 1;
			uint8_t increment_mode : 1;
			uint8_t pattern_sprite : 1;
			uint8_t pattern_background : 1;
			uint8_t sprite_size : 1;
			uint8_t slave_mode : 1;
			uint8_t enable_nmi : 1;
		};

		uint8_t reg;
	} control;

    union loopy_register
    {
        struct
        {
            uint16_t coarse_x : 5;
			uint16_t coarse_y : 5;
			uint16_t nametable_x : 1;
			uint16_t nametable_y : 1;
			uint16_t fine_y : 3;
			uint16_t unused : 1;
        };
		uint16_t reg = 0x0000;
    };

    loopy_register m_lVRamAddr;
    loopy_register m_lTRamAddr;

    uint8_t m_uFineX = 0x00;

    uint8_t m_uAddressLatch = 0x00;
	uint8_t m_uPpuDataBuffer = 0x00;
    
    int16_t scanline = 0;
    int16_t cycle = 0;

    uint8_t m_uBgNextTileId = 0x00;
    uint8_t m_uBgNextTileAttrib = 0x00;
    uint8_t m_uBgNextTileLsb = 0x00;
    uint8_t m_uBgNextTileMsb = 0x00;

	uint16_t m_uBgShifterPatternLo = 0x0000;
	uint16_t m_uBgShifterPatternHi = 0x0000;
	uint16_t m_uBgShifterPatternAttribLo  = 0x0000;
	uint16_t m_uBgShifterPatternAttribHi  = 0x0000;

public:
    uint8_t cpuRead(uint16_t addr, bool bRdOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    uint8_t ppuRead(uint16_t addr, bool bRdOnly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

private:
    std::shared_ptr<Cartridge> m_pCart;
public:
    void ConnectCartridge(const std::shared_ptr<Cartridge>& pCartridge);
    void clock();
	void reset();
    bool m_bNmi = false;

private:
    struct sObjectAttributeEntry
    {
        uint8_t y;
        uint8_t id;
        uint8_t attribute;
        uint8_t x;
    } OAM[64];

    uint8_t m_uOamAddr = 0x00;
    sObjectAttributeEntry m_sSpriteScanLine[8];
    uint8_t m_uSpriteCount;
    uint8_t m_uSpriteShifterPatternLo[8];
    uint8_t m_uSpriteShifterPatternHi[8];

    bool m_bSpriteZeroHitPossible = false;
    bool m_bSpriteZeroBeingRendered = false;

public:
    uint8_t* m_pOAM = (uint8_t*)OAM;

};