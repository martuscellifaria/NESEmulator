/*
	olc::NES - Part #4 - Buses, Rams, Roms & Mappers
	"Thanks Dad for believing computers were gonna be a big deal..." - javidx9

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018-2019 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions
	are met:

	1. Redistributions or derivations of source code must retain the above
	copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce
	the above copyright notice. This list of conditions and the following
	disclaimer must be reproduced in the documentation and/or other
	materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its
	contributors may be used to endorse or promote products derived
	from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


	Relevant Video: https://youtu.be/-THeUXqR3zY

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
				https://www.youtube.com/javidx9extra
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Patreon:	https://www.patreon.com/javidx9
	Homepage:	https://www.onelonecoder.com

	Author
	~~~~~~
	David Barr, aka javidx9, ©OneLoneCoder 2019
*/

#include <iostream>
#include <sstream>

#include "Bus.h"
#include "chip6502.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"



class Demo_olc2C02 : public olc::PixelGameEngine
{
public:
	Demo_olc2C02() { sAppName = "Alex Emulator"; }

private: 
	// The NES
	Bus nes;
	std::shared_ptr<Cartridge> cart;
	bool bEmulationRun = false;
	float fResidualTime = 0.0f;

	uint8_t nSelectedPalette = 0x00;

private: 
	// Support Utilities
	std::map<uint16_t, std::string> mapAsm;

	std::string hex(uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
	{
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++)
		{
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for (int col = 0; col < nColumns; col++)
			{
				sOffset += " " + hex(nes.cpuRead(nAddr, true), 2);
				nAddr += 1;
			}
			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

	void DrawCpu(int x, int y)
	{
		std::string status = "STATUS: ";
		DrawString(x , y , "STATUS:", olc::WHITE);
		DrawString(x  + 64, y, "N", nes.cpu.m_uStatus & Chip6502::N ? olc::GREEN : olc::RED);
		DrawString(x  + 80, y , "V", nes.cpu.m_uStatus & Chip6502::V ? olc::GREEN : olc::RED);
		DrawString(x  + 96, y , "-", nes.cpu.m_uStatus & Chip6502::U ? olc::GREEN : olc::RED);
		DrawString(x  + 112, y , "B", nes.cpu.m_uStatus & Chip6502::B ? olc::GREEN : olc::RED);
		DrawString(x  + 128, y , "D", nes.cpu.m_uStatus & Chip6502::D ? olc::GREEN : olc::RED);
		DrawString(x  + 144, y , "I", nes.cpu.m_uStatus & Chip6502::I ? olc::GREEN : olc::RED);
		DrawString(x  + 160, y , "Z", nes.cpu.m_uStatus & Chip6502::Z ? olc::GREEN : olc::RED);
		DrawString(x  + 178, y , "C", nes.cpu.m_uStatus & Chip6502::C ? olc::GREEN : olc::RED);
		DrawString(x , y + 10, "PC: $" + hex(nes.cpu.m_uPc, 4));
		DrawString(x , y + 20, "A: $" +  hex(nes.cpu.m_uAccumulator, 2) + "  [" + std::to_string(nes.cpu.m_uAccumulator) + "]");
		DrawString(x , y + 30, "X: $" +  hex(nes.cpu.m_uX, 2) + "  [" + std::to_string(nes.cpu.m_uX) + "]");
		DrawString(x , y + 40, "Y: $" +  hex(nes.cpu.m_uY, 2) + "  [" + std::to_string(nes.cpu.m_uY) + "]");
		DrawString(x , y + 50, "Stack P: $" + hex(nes.cpu.m_uStkp, 4));
	}

	void DrawCode(int x, int y, int nLines)
	{
		auto it_a = mapAsm.find(nes.cpu.m_uPc);
		int nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			DrawString(x, nLineY, (*it_a).second, olc::CYAN);
			while (nLineY < (nLines * 10) + y)
			{
				nLineY += 10;
				if (++it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}

		it_a = mapAsm.find(nes.cpu.m_uPc);
		nLineY = (nLines >> 1) * 10 + y;
		if (it_a != mapAsm.end())
		{
			while (nLineY > y)
			{
				nLineY -= 10;
				if (--it_a != mapAsm.end())
				{
					DrawString(x, nLineY, (*it_a).second);
				}
			}
		}
	}

	bool OnUserCreate()
	{
		// Load the cartridge
		cart = std::make_shared<Cartridge>("../smb.nes");
		
		if (!cart->imageValid())
			return false;

		// Insert into NES
		nes.insertCartridge(cart);
					
		// Extract dissassembly
		mapAsm = nes.cpu.disassemble(0x0000, 0xFFFF);

		// Reset NES
		nes.reset();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		Clear(olc::DARK_BLUE);

		// Sneaky peek of controller input in next video! ;P
		nes.m_uController[0] = 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::X).bHeld ? 0x80 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::Z).bHeld ? 0x40 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::A).bHeld ? 0x20 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::S).bHeld ? 0x10 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::UP).bHeld ? 0x08 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::DOWN).bHeld ? 0x04 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::LEFT).bHeld ? 0x02 : 0x00;
		nes.m_uController[0] |= GetKey(olc::Key::RIGHT).bHeld ? 0x01 : 0x00;

		if (GetKey(olc::Key::SPACE).bPressed) bEmulationRun = !bEmulationRun;
		if (GetKey(olc::Key::R).bPressed) nes.reset();
		if (GetKey(olc::Key::P).bPressed) (++nSelectedPalette) &= 0x07;

		if (bEmulationRun)
		{
			if (fResidualTime > 0.0f)
				fResidualTime -= fElapsedTime;
			else
			{
				fResidualTime += (1.0f / 60.0f) - fElapsedTime;
				do { nes.clock(); } while (!nes.ppu.m_bFrameComplete);
				nes.ppu.m_bFrameComplete = false;
			}
		}
		else
		{
			// Emulate code step-by-step
			if (GetKey(olc::Key::C).bPressed)
			{
				// Clock enough times to execute a whole CPU instruction
				do { nes.clock(); } while (!nes.cpu.complete());
				// CPU clock runs slower than system clock, so it may be
				// complete for additional system clock cycles. Drain
				// those out
				do { nes.clock(); } while (nes.cpu.complete());
			}

			// Emulate one whole frame
			if (GetKey(olc::Key::F).bPressed)
			{
				// Clock enough times to draw a single frame
				do { nes.clock(); } while (!nes.ppu.m_bFrameComplete);
				// Use residual clock cycles to complete current instruction
				do { nes.clock(); } while (!nes.cpu.complete());
				// Reset frame completion flag
				nes.ppu.m_bFrameComplete = false;
			}
		}


		

		DrawCpu(516, 2);
		//DrawCode(516, 72, 26);

		for (int i = 0; i < 26; i++)
		{
			std::string s = hex(i, 2) + ": (" + std::to_string(nes.ppu.m_pOAM[i * 4 + 3])
				+ ", " + std::to_string(nes.ppu.m_pOAM[i * 4 + 0]) + ") "
				+ "ID: " + hex(nes.ppu.m_pOAM[i * 4 + 1], 2) +
				+" AT: " + hex(nes.ppu.m_pOAM[i * 4 + 2], 2);
			DrawString(516, 72 + i * 10, s);
		}

		// Draw Palettes & Pattern Tables ==============================================
		const int nSwatchSize = 6;
		for (int p = 0; p < 8; p++) // For each palette
			for(int s = 0; s < 4; s++) // For each index
				FillRect(516 + p * (nSwatchSize * 5) + s * nSwatchSize, 340, 
					nSwatchSize, nSwatchSize, nes.ppu.GetColourFromPaletteRam(p, s));
		
		// Draw selection reticule around selected palette
		DrawRect(516 + nSelectedPalette * (nSwatchSize * 5) - 1, 339, (nSwatchSize * 4), nSwatchSize, olc::WHITE);

		// Generate Pattern Tables
		DrawSprite(516, 348, &nes.ppu.GetPatternTable(0, nSelectedPalette));
		DrawSprite(648, 348, &nes.ppu.GetPatternTable(1, nSelectedPalette));

		// Draw rendered output ========================================================
		DrawSprite(0, 0, &nes.ppu.GetScreen(), 2);
		return true;
	}
};





int main()
{
	Demo_olc2C02 demo;
	demo.Construct(780, 480, 2, 2);
	demo.Start();
	return 0;
}