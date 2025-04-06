#include "chip2C02.h"

Chip2C02::Chip2C02()
{
    m_pPalScreen[0x00] = olc::Pixel(84, 84, 84);
	m_pPalScreen[0x01] = olc::Pixel(0, 30, 116);
	m_pPalScreen[0x02] = olc::Pixel(8, 16, 144);
	m_pPalScreen[0x03] = olc::Pixel(48, 0, 136);
	m_pPalScreen[0x04] = olc::Pixel(68, 0, 100);
	m_pPalScreen[0x05] = olc::Pixel(92, 0, 48);
	m_pPalScreen[0x06] = olc::Pixel(84, 4, 0);
	m_pPalScreen[0x07] = olc::Pixel(60, 24, 0);
	m_pPalScreen[0x08] = olc::Pixel(32, 42, 0);
	m_pPalScreen[0x09] = olc::Pixel(8, 58, 0);
	m_pPalScreen[0x0A] = olc::Pixel(0, 64, 0);
	m_pPalScreen[0x0B] = olc::Pixel(0, 60, 0);
	m_pPalScreen[0x0C] = olc::Pixel(0, 50, 60);
	m_pPalScreen[0x0D] = olc::Pixel(0, 0, 0);
	m_pPalScreen[0x0E] = olc::Pixel(0, 0, 0);
	m_pPalScreen[0x0F] = olc::Pixel(0, 0, 0);

	m_pPalScreen[0x10] = olc::Pixel(152, 150, 152);
	m_pPalScreen[0x11] = olc::Pixel(8, 76, 196);
	m_pPalScreen[0x12] = olc::Pixel(48, 50, 236);
	m_pPalScreen[0x13] = olc::Pixel(92, 30, 228);
	m_pPalScreen[0x14] = olc::Pixel(136, 20, 176);
	m_pPalScreen[0x15] = olc::Pixel(160, 20, 100);
	m_pPalScreen[0x16] = olc::Pixel(152, 34, 32);
	m_pPalScreen[0x17] = olc::Pixel(120, 60, 0);
	m_pPalScreen[0x18] = olc::Pixel(84, 90, 0);
	m_pPalScreen[0x19] = olc::Pixel(40, 114, 0);
	m_pPalScreen[0x1A] = olc::Pixel(8, 124, 0);
	m_pPalScreen[0x1B] = olc::Pixel(0, 118, 40);
	m_pPalScreen[0x1C] = olc::Pixel(0, 102, 120);
	m_pPalScreen[0x1D] = olc::Pixel(0, 0, 0);
	m_pPalScreen[0x1E] = olc::Pixel(0, 0, 0);
	m_pPalScreen[0x1F] = olc::Pixel(0, 0, 0);

	m_pPalScreen[0x20] = olc::Pixel(236, 238, 236);
	m_pPalScreen[0x21] = olc::Pixel(76, 154, 236);
	m_pPalScreen[0x22] = olc::Pixel(120, 124, 236);
	m_pPalScreen[0x23] = olc::Pixel(176, 98, 236);
	m_pPalScreen[0x24] = olc::Pixel(228, 84, 236);
	m_pPalScreen[0x25] = olc::Pixel(236, 88, 180);
	m_pPalScreen[0x26] = olc::Pixel(236, 106, 100);
	m_pPalScreen[0x27] = olc::Pixel(212, 136, 32);
	m_pPalScreen[0x28] = olc::Pixel(160, 170, 0);
	m_pPalScreen[0x29] = olc::Pixel(116, 196, 0);
	m_pPalScreen[0x2A] = olc::Pixel(76, 208, 32);
	m_pPalScreen[0x2B] = olc::Pixel(56, 204, 108);
	m_pPalScreen[0x2C] = olc::Pixel(56, 180, 204);
	m_pPalScreen[0x2D] = olc::Pixel(60, 60, 60);
	m_pPalScreen[0x2E] = olc::Pixel(0, 0, 0);
	m_pPalScreen[0x2F] = olc::Pixel(0, 0, 0);

	m_pPalScreen[0x30] = olc::Pixel(236, 238, 236);
	m_pPalScreen[0x31] = olc::Pixel(168, 204, 236);
	m_pPalScreen[0x32] = olc::Pixel(188, 188, 236);
	m_pPalScreen[0x33] = olc::Pixel(212, 178, 236);
	m_pPalScreen[0x34] = olc::Pixel(236, 174, 236);
	m_pPalScreen[0x35] = olc::Pixel(236, 174, 212);
	m_pPalScreen[0x36] = olc::Pixel(236, 180, 176);
	m_pPalScreen[0x37] = olc::Pixel(228, 196, 144);
	m_pPalScreen[0x38] = olc::Pixel(204, 210, 120);
	m_pPalScreen[0x39] = olc::Pixel(180, 222, 120);
	m_pPalScreen[0x3A] = olc::Pixel(168, 226, 144);
	m_pPalScreen[0x3B] = olc::Pixel(152, 226, 180);
	m_pPalScreen[0x3C] = olc::Pixel(160, 214, 228);
	m_pPalScreen[0x3D] = olc::Pixel(160, 162, 160);
	m_pPalScreen[0x3E] = olc::Pixel(0, 0, 0);
	m_pPalScreen[0x3F] = olc::Pixel(0, 0, 0);

	m_sSprScreen = new olc::Sprite(256, 240);
	m_sSprNameTable[0] = new olc::Sprite(256, 240);
	m_sSprNameTable[1] = new olc::Sprite(256, 240);
	m_sSprPatternTable[0] = new olc::Sprite(128, 128);
	m_sSprPatternTable[1] = new olc::Sprite(128, 128);
}

Chip2C02::~Chip2C02()
{
    delete m_sSprScreen;
	delete m_sSprNameTable[0];
	delete m_sSprNameTable[1];
	delete m_sSprPatternTable[0];
	delete m_sSprPatternTable[1];
}

olc::Sprite& Chip2C02::GetScreen()
{
	return *m_sSprScreen;
}

olc::Sprite & Chip2C02::GetNameTable(uint8_t i)
{
	return *m_sSprNameTable[i];
}

olc::Sprite & Chip2C02::GetPatternTable(uint8_t i, uint8_t palette)
{
	for (uint16_t nTileY = 0; nTileY < 16; nTileY++)
	{
		for (uint16_t nTileX = 0; nTileX < 16; nTileX++)
		{
			uint16_t nOffset = nTileY * 256 + nTileX * 16;

			for (uint16_t row = 0; row < 8; row++)
			{
				uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffset + row + 0x0000);
				uint8_t tile_msb = ppuRead(i * 0x1000 + nOffset + row + 0x0008);

				for (uint16_t col = 0; col < 8; col++)
				{
					uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01);
					tile_lsb >>= 1; tile_msb >>= 1;

					m_sSprPatternTable[i]->SetPixel(nTileX * 8 + (7 - col), nTileY * 8 + row, GetColourFromPaletteRam(palette, pixel));
				}
			}
		}
	}
	return *m_sSprPatternTable[i];
}

olc::Pixel& Chip2C02::GetColourFromPaletteRam(uint8_t palette, uint8_t pixel)
{
	return m_pPalScreen[ppuRead(0x3F00 + (palette << 2) + pixel) & 0x3F];
}

uint8_t Chip2C02::cpuRead(uint16_t addr, bool bRdOnly)
{
    uint8_t data = 0x00;
	if (bRdOnly)
	{
		switch (addr)
		{
		case 0x0000: // Control
			data = control.reg;
			break;
		case 0x0001: // Mask
			data = mask.reg;
			break;
		case 0x0002: // Status
			data = status.reg;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
		}
	}
	else
	{
		switch (addr)
		{
			case 0x0000: 
				break;
			case 0x0001:
				break;
			case 0x0002:
				data = (status.reg & 0xE0) | (m_uPpuDataBuffer & 0x1F);
				status.vertical_blank = 0;
				m_uAddressLatch = 0;
				break;
			case 0x0003:
				break;
			case 0x0004: break;
			case 0x0005: break;
			case 0x0006: break;
			case 0x0007:
				data = m_uPpuDataBuffer;
				m_uPpuDataBuffer = ppuRead(m_lVRamAddr.reg);
				if (m_lVRamAddr.reg >= 0x3F00) data = m_uPpuDataBuffer;
				m_lVRamAddr.reg += (control.increment_mode ? 32 : 1);
				break;
		}
	}
    return data;
}
void Chip2C02::cpuWrite(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
        case 0x0000:
			control.reg = data;
			m_lTRamAddr.nametable_x = control.nametable_x;
			m_lTRamAddr.nametable_y = control.nametable_y;
        break;
        case 0x0001:
			mask.reg = data;
        break;
        case 0x0002:
        break;
        case 0x0003:
        break;
        case 0x0004:
        break;
        case 0x0005:
			if (m_uAddressLatch == 0)
			{
				m_uFineX = data & 0x07;
				m_lTRamAddr.coarse_x = data >> 3;
				m_uAddressLatch = 1;
			}
			else
			{
				m_lTRamAddr.fine_y = data & 0x07;
				m_lTRamAddr.coarse_y = data >> 3;
				m_uAddressLatch = 0;
			}
        break;
        case 0x0006:
			if (m_uAddressLatch == 0)
			{
				m_lTRamAddr.reg = (uint16_t)((data & 0x3F) << 8) | (m_lTRamAddr.reg & 0x00FF);
				m_uAddressLatch = 1;
			}
			else
			{
				m_lTRamAddr.reg = (m_lTRamAddr.reg & 0xFF00) | data;
				m_lVRamAddr = m_lTRamAddr;
				m_uAddressLatch = 0;
			}
        	break;
        case 0x0007:
			ppuWrite(m_lVRamAddr.reg, data);
			m_lVRamAddr.reg += (control.increment_mode ? 32 : 1);
        break;
    }
}


uint8_t Chip2C02::ppuRead(uint16_t addr, bool bRdOnly)
{
    uint8_t data = 0x00;
    addr &= 0x3FFF;

    if (m_pCart->ppuRead(addr, data))
    {

    }
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		data = m_uTablePattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		addr &= 0x0FFF;

		if (m_pCart->mirror == Cartridge::MIRROR::VERTICAL)
		{
			// Vertical
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = m_uTableName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = m_uTableName[1][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = m_uTableName[0][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = m_uTableName[1][addr & 0x03FF];
		}
		else if (m_pCart->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = m_uTableName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = m_uTableName[0][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = m_uTableName[1][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = m_uTableName[1][addr & 0x03FF];
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		data = m_uTablePalette[addr] & (mask.grayscale ? 0x30 : 0x3F);
	}

    return data;
}

void Chip2C02::ppuWrite(uint16_t addr, uint8_t data)
{
    addr &= 0x3FFF;

    if (m_pCart->cpuWrite(addr, data))
    {

    }
	else if (addr >= 0x0000 && addr <= 0x1FFF)
	{
		m_uTablePattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		addr &= 0x0FFF;
		if (m_pCart->mirror == Cartridge::MIRROR::VERTICAL)
		{
			// Vertical
			if (addr >= 0x0000 && addr <= 0x03FF)
				m_uTableName[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF)
				m_uTableName[1][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				m_uTableName[0][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				m_uTableName[1][addr & 0x03FF] = data;
		}
		else if (m_pCart->mirror == Cartridge::MIRROR::HORIZONTAL)
		{
			// Horizontal
			if (addr >= 0x0000 && addr <= 0x03FF)
				m_uTableName[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF)
				m_uTableName[0][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				m_uTableName[1][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				m_uTableName[1][addr & 0x03FF] = data;
		}
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		m_uTablePalette[addr] = data;
	}
}

void Chip2C02::ConnectCartridge(const std::shared_ptr<Cartridge>& pCartridge)
{
    this->m_pCart = pCartridge;
}

void Chip2C02::reset()
{
	m_uFineX = 0x00;
	m_uAddressLatch = 0x00;
	m_uPpuDataBuffer = 0x00;
	scanline = 0;
	cycle = 0;
	m_uBgNextTileId = 0x00;
	m_uBgNextTileAttrib = 0x00;
	m_uBgNextTileLsb = 0x00;
	m_uBgNextTileMsb = 0x00;
	m_uBgShifterPatternLo = 0x0000;
	m_uBgShifterPatternHi = 0x0000;
	m_uBgShifterPatternAttribLo = 0x0000;
	m_uBgShifterPatternAttribHi = 0x0000;
	status.reg = 0x00;
	mask.reg = 0x00;
	control.reg = 0x00;
	m_lVRamAddr.reg = 0x0000;
	m_lTRamAddr.reg = 0x0000;
}

void Chip2C02::clock()
{
	auto IncrementScrollX = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			if (m_lVRamAddr.coarse_x == 31)
			{
				m_lVRamAddr.coarse_x = 0;
				m_lVRamAddr.nametable_x = ~m_lVRamAddr.nametable_x;
			}
			else
			{
				m_lVRamAddr.coarse_x++;
			}
		}
	};
	
	auto IncrementScrollY = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			if (m_lVRamAddr.fine_y < 7)
			{
				m_lVRamAddr.fine_y++;
			}
			else
			{
				m_lVRamAddr.fine_y = 0;

				if (m_lVRamAddr.coarse_y == 29)
				{
					m_lVRamAddr.coarse_y = 0;
					m_lVRamAddr.nametable_y = ~m_lVRamAddr.nametable_y;
				}
				else if (m_lVRamAddr.coarse_y == 31)
				{
					m_lVRamAddr.coarse_y = 0;
				}
				else
				{
					m_lVRamAddr.coarse_y++;
				}
			}
		}
	};

	auto TransferAddressX = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			m_lVRamAddr.nametable_x = m_lTRamAddr.nametable_x;
			m_lVRamAddr.coarse_x    = m_lTRamAddr.coarse_x;
		}
	};
	
	auto TransferAddressY = [&]()
	{
		if (mask.render_background || mask.render_sprites)
		{
			m_lVRamAddr.fine_y      = m_lTRamAddr.fine_y;
			m_lVRamAddr.nametable_y = m_lTRamAddr.nametable_y;
			m_lVRamAddr.coarse_y    = m_lTRamAddr.coarse_y;
		}
	};
	
	auto LoadBackgroundShifters = [&]()
	{
		m_uBgShifterPatternLo = (m_uBgShifterPatternLo & 0xFF00) | m_uBgNextTileLsb;
		m_uBgShifterPatternHi = (m_uBgShifterPatternHi & 0xFF00) | m_uBgNextTileMsb;

		m_uBgShifterPatternAttribLo  = (m_uBgShifterPatternAttribLo & 0xFF00) | ((m_uBgNextTileAttrib & 0b01) ? 0xFF : 0x00);
		m_uBgShifterPatternAttribHi  = (m_uBgShifterPatternAttribHi & 0xFF00) | ((m_uBgNextTileAttrib & 0b10) ? 0xFF : 0x00);
	};

	auto UpdateShifters = [&]()
	{
		if (mask.render_background)
		{
			m_uBgShifterPatternLo <<= 1;
			m_uBgShifterPatternHi <<= 1;

			m_uBgShifterPatternAttribLo <<= 1;
			m_uBgShifterPatternAttribHi <<= 1;
		}
	};

	if (scanline >= -1 && scanline < 240)
	{
		if (scanline == 0 && cycle == 0)
		{
			cycle = 1;
		}

		if (scanline == -1 && cycle == 1)
		{
			status.vertical_blank = 0;
		}

		if ((cycle >= 2 && cycle < 258) || (cycle >= 321 && cycle < 338))
		{
			UpdateShifters();
			switch ((cycle - 1) % 8)
			{
				case 0:
					LoadBackgroundShifters();
					m_uBgNextTileId = ppuRead(0x2000 | (m_lVRamAddr.reg & 0x0FFF));
					break;
				case 2:
				m_uBgNextTileAttrib = ppuRead(0x23C0 | (m_lVRamAddr.nametable_y << 11) 
														| (m_lVRamAddr.nametable_x << 10) 
														| ((m_lVRamAddr.coarse_y >> 2) << 3) 
														| (m_lVRamAddr.coarse_x >> 2));

					if (m_lVRamAddr.coarse_y & 0x02) m_uBgNextTileAttrib >>= 4;
					if (m_lVRamAddr.coarse_x & 0x02) m_uBgNextTileAttrib >>= 2;
					m_uBgNextTileAttrib &= 0x03;
					break;
				case 4:
				m_uBgNextTileLsb = ppuRead((control.pattern_background << 12) 
										+ ((uint16_t)m_uBgNextTileId << 4) 
										+ (m_lVRamAddr.fine_y) + 0);
					break;
				case 6:
				m_uBgNextTileMsb = ppuRead((control.pattern_background << 12)
											+ ((uint16_t)m_uBgNextTileId << 4)
											+ (m_lVRamAddr.fine_y) + 8);
					break;
				case 7:
					IncrementScrollX();
					break;
			}
		}

		if (cycle == 256)
		{
			IncrementScrollY();
		}

		if (cycle == 257)
		{
			LoadBackgroundShifters();
			TransferAddressX();
		}

		if (cycle == 338 || cycle == 340)
		{
			m_uBgNextTileId = ppuRead(0x2000 | (m_lVRamAddr.reg & 0x0FFF));
		}

		if (scanline == -1 && cycle >= 280 && cycle < 305)
		{
			TransferAddressY();
		}
	}

	if (scanline == 240)
	{
	}

	if (scanline >= 241 && cycle < 261)
	{
		if (scanline == 241 && cycle == 1)
		{
			status.vertical_blank = 1;

			if (control.enable_nmi)
			{
				m_bNmi = true;
			}
		}
	}

	uint8_t bg_pixel = 0x00;
	uint8_t bg_palette = 0x00;

	if (mask.render_background)
	{
		uint16_t bit_mux = 0x8000 >> m_uFineX;
		uint8_t p0_pixel = (m_uBgShifterPatternLo & bit_mux) > 0;
		uint8_t p1_pixel = (m_uBgShifterPatternHi & bit_mux) > 0;

		bg_pixel = (p1_pixel << 1) | p0_pixel;
		
		uint8_t bg_pal0 = (m_uBgShifterPatternAttribLo & bit_mux) > 0;
		uint8_t bg_pal1 = (m_uBgShifterPatternAttribHi & bit_mux) > 0;

		bg_palette = (bg_pal1 << 1) | bg_pal0;
	}
    
	m_sSprScreen->SetPixel(cycle - 1, scanline, GetColourFromPaletteRam(bg_palette, bg_pixel));
    
	cycle++;
    if (cycle >= 341)
    {
        cycle = 0;
        scanline++;
        if (scanline >= 261)
        {
            scanline = -1;
            m_bFrameComplete = true;
        }
    }
}