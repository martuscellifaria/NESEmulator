#include "Cartridge.h"

Cartridge::Cartridge(const std::string& sFileName)
{
	// iNES Format Header
	struct sHeader
	{
		char name[4];
		uint8_t prg_rom_chunks;
		uint8_t chr_rom_chunks;
		uint8_t mapper1;
		uint8_t mapper2;
		uint8_t prg_ram_size;
		uint8_t tv_system1;
		uint8_t tv_system2;
		char unused[5];
	} header;

	bImageValid = false;

	std::ifstream ifs;
	ifs.open(sFileName, std::ifstream::binary);
	if (ifs.is_open())
	{
		ifs.read((char*)&header, sizeof(sHeader));
		
		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		// Determine Mapper ID
		m_nMapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		mirror = (header.mapper1 & 0x01) ? VERTICAL : HORIZONTAL;

		// "Discover" File Format
		uint8_t nFileType = 1;

		if (nFileType == 0)
		{

		}

		if (nFileType == 1)
		{
			m_nPRGBanks = header.prg_rom_chunks;
			m_vPRGMemory.resize(m_nPRGBanks * 16384);
			ifs.read((char*)m_vPRGMemory.data(), m_vPRGMemory.size());

			m_nCHRBanks = header.chr_rom_chunks;


			if (m_nCHRBanks == 0)
			{
				m_vCHRMemory.resize(8192);
			}
			else
			{
				m_vCHRMemory.resize(m_nCHRBanks * 8192);
			}
			ifs.read((char*)m_vCHRMemory.data(), m_vCHRMemory.size());
		}

		if (nFileType == 2)
		{

		}

		// Load appropriate mapper
		switch (m_nMapperID)
		{
		case   0: m_pMapper= std::make_shared<Mapper_000>(m_nPRGBanks, m_nCHRBanks); break;
		//case   2: pMapper = std::make_shared<Mapper_002>(nPRGBanks, nCHRBanks); break;
		//case   3: pMapper = std::make_shared<Mapper_003>(nPRGBanks, nCHRBanks); break;
		//case  66: pMapper = std::make_shared<Mapper_066>(nPRGBanks, nCHRBanks); break;
		}

		bImageValid = true;
		ifs.close();
	}

}

Cartridge::~Cartridge()
{
    
}

bool Cartridge::ImageValid()
{
	return bImageValid;
}

bool Cartridge::cpuRead(uint16_t addr, uint8_t& data)
{
    uint32_t mapped_addr = 0;
    if(m_pMapper->cpuMapRead(addr, mapped_addr))
    {
        data = m_vPRGMemory[mapped_addr];
        return true;
    }
    else
        return false;
}

bool Cartridge::cpuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if(m_pMapper->cpuMapWrite(addr, mapped_addr, data))
    {
        m_vPRGMemory[mapped_addr] = data;
        return true;
    }
    else
        return false;
}

bool Cartridge::ppuRead(uint16_t addr,  uint8_t& data)
{
    uint32_t mapped_addr = 0;
    if(m_pMapper->ppuMapRead(addr, mapped_addr))
    {
        data = m_vCHRMemory[mapped_addr];
        return true;
    }
    return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
    uint32_t mapped_addr = 0;
    if(m_pMapper->ppuMapWrite(addr, mapped_addr))
    {
        m_vCHRMemory[mapped_addr] = data;
        return true;
    }
    return false;

}

void Cartridge::reset()
{
	if (m_pMapper != nullptr)
    {
        m_pMapper->reset();
    }
}