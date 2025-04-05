#include <chip6502.h>
#include "Bus.h"

Chip6502::Chip6502()
{
    using a = Chip6502;
	m_vLookup = 
	{
		{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
		{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
		{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
		{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
	};
}

Chip6502::~Chip6502()
{
    
}

// Addressing Modes
uint8_t Chip6502::IMP()
{
    m_uFetched = m_uAccumulator;
    return 0;
}

uint8_t Chip6502::IMM()
{
    m_uAddrAbs = m_uPc++;
    return 0;
}

uint8_t Chip6502::ZP0()
{
    m_uAddrAbs = read(m_uPc);
    m_uPc++;
    m_uAddrAbs &= 0x00FF;
    return 0;
}

uint8_t Chip6502::ZPX()
{
    m_uAddrAbs = (read(m_uPc) + m_uX);
    m_uPc++;
    m_uAddrAbs &= 0x00FF;
    return 0;
}

uint8_t Chip6502::ZPY()
{
    m_uAddrAbs = (read(m_uPc) + m_uY);
    m_uPc++;
    m_uAddrAbs &= 0x00FF;
    return 0;
}

uint8_t Chip6502::REL()
{
    m_uAddrRel = read(m_uPc);
    m_uPc++;

    if (m_uAddrRel & 0x80)
    {
        m_uAddrRel|= 0xFF00;
    }

    return 0;
}

uint8_t Chip6502::ABS()
{
    uint16_t lo = read(m_uPc);
    m_uPc++;
    uint16_t hi = read(m_uPc);
    m_uPc++;
    m_uAddrAbs = (hi << 8) | lo;
    return 0;
}

uint8_t Chip6502::ABX()
{
    uint16_t lo = read(m_uPc);
    m_uPc++;
    uint16_t hi = read(m_uPc);
    m_uPc++;
    m_uAddrAbs = (hi << 8) | lo;
    m_uAddrAbs += m_uX;

    if ((m_uAddrAbs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    return 0;
}

uint8_t Chip6502::ABY()
{
    uint16_t lo = read(m_uPc);
    m_uPc++;
    uint16_t hi = read(m_uPc);
    m_uPc++;
    m_uAddrAbs = (hi << 8) | lo;
    m_uAddrAbs += m_uY;
    
    if ((m_uAddrAbs & 0xFF00) != (hi << 8))
    {
        return 1;
    }
    return 0;
}

uint8_t Chip6502::IND()
{
    uint16_t ptr_lo = read(m_uPc);
    m_uPc++;
    uint16_t ptr_hi = read(m_uPc);
    m_uPc++;
    
    uint16_t ptr = (ptr_hi << 8) | ptr_lo;

    if (ptr_lo == 0xFF00)
    {
        m_uAddrAbs = (read(ptr & 0xFF00) << 8)| read(ptr + 0);
        return 0;
    }

    m_uAddrAbs = (read(ptr + 1) << 8) | read(ptr + 0);
    return 0;
}

uint8_t Chip6502::IZX()
{
    uint16_t t = read(m_uPc);
    m_uPc++;
    
    uint16_t lo = read((uint16_t)(t + (u_int16_t)m_uX) & 0x00FF);
    uint16_t hi = read((uint16_t)(t + (u_int16_t)m_uX + 1) & 0x00FF);

    m_uAddrAbs = (hi << 8) | lo;
    return 0;
}

uint8_t Chip6502::IZY()
{
    uint16_t t = read(m_uPc);
    m_uPc++;
    
    uint16_t lo = read(t & 0x00FF);
    uint16_t hi = read((t + 1) & 0x00FF);

    m_uAddrAbs = (hi << 8) | lo;
    m_uAddrAbs += m_uY;

    if ((m_uAddrAbs & 0xFF00) != (hi << 8))
    {
        return 1;
    }

    return 0;
}

uint8_t Chip6502::fetch()
{
    if (!(m_vLookup[m_uOpcode].addrMode == &Chip6502::IMP))
    {
        m_uFetched = read(m_uAddrAbs);
    }
    return m_uFetched;
}



// OPCODES (6502 ASSEMBLY INSTRUCTIONS)


uint8_t Chip6502::ADC()
{
    fetch();
    m_uTemp = (uint16_t)m_uAccumulator + (uint16_t)m_uFetched + (uint16_t)GetFlag(C);
    SetFlag(C, m_uTemp > 255);
    SetFlag(Z, (m_uTemp & 0x00FF) == 0);
    SetFlag(V, (~((uint16_t)m_uAccumulator ^ (uint16_t)m_uFetched) & ((uint16_t)m_uAccumulator ^ (uint16_t)m_uTemp)) & 0x0080);
    SetFlag(N, m_uTemp & 0x80);
    m_uAccumulator = m_uTemp & 0x00FF;
	return 1;
}


uint8_t Chip6502::SBC()
{
    fetch();
    uint16_t value = (uint16_t)m_uFetched ^ 0x00FF;
    m_uTemp = (uint16_t)m_uAccumulator + (uint16_t)value + (uint16_t)GetFlag(C);
    SetFlag(C, m_uTemp & 0xFF00);
    SetFlag(Z, (m_uTemp & 0x00FF) == 0);
    SetFlag(V, (m_uTemp ^ (uint16_t)m_uAccumulator) & (m_uTemp ^ value) & 0x0080);
    SetFlag(N, m_uTemp & 0x80);
    m_uAccumulator = m_uTemp & 0x00FF;
	return 1;
}



uint8_t Chip6502::AND()
{
    fetch();
    m_uAccumulator = m_uAccumulator & m_uFetched;
    SetFlag(Z, m_uAccumulator == 0x00);
    SetFlag(N, m_uAccumulator & 0x80);
    return 1;
}

uint8_t Chip6502::ASL()
{
	fetch();
	m_uTemp = (uint16_t)m_uFetched << 1;
	SetFlag(C, (m_uTemp & 0xFF00) > 0);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x00);
	SetFlag(N, m_uTemp & 0x80);
	if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IMP)
    {
        m_uAccumulator = m_uTemp & 0x00FF;
    }
	else
    {
		write(m_uAddrAbs, m_uTemp & 0x00FF);
    }
	return 0;
}

uint8_t Chip6502::BCC()
{
	if (GetFlag(C) == 0)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if ((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::BCS()
{
    if (GetFlag(C) == 1)
    {
        m_uCycles++;
        m_uAddrAbs = m_uPc + m_uAddrRel;
        if ((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {
            m_uCycles++;
        }
        m_uPc = m_uAddrAbs;
    }
    return 0;
}

uint8_t Chip6502::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::BIT()
{
	fetch();
	m_uTemp = m_uAccumulator & m_uFetched;
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x00);
	SetFlag(N, m_uFetched & (1 << 7));
	SetFlag(V, m_uFetched & (1 << 6));
	return 0;
}

uint8_t Chip6502::BMI()
{
	if (GetFlag(N) == 1)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::BNE()
{
	if (GetFlag(Z) == 0)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::BPL()
{
	if (GetFlag(N) == 0)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::BRK()
{
	m_uPc++;
	
	SetFlag(I, true);
	write(0x0100 + m_uStkp, (m_uPc >> 8) & 0x00FF);
	m_uStkp--;
	write(0x0100 + m_uStkp, m_uPc & 0x00FF);
	m_uStkp--;

	SetFlag(B, true);
	write(0x0100 + m_uStkp, m_uStatus);
	m_uStkp--;
	SetFlag(B, false);

	m_uPc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}

uint8_t Chip6502::BVC()
{
	if (GetFlag(V) == 0)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::BVS()
{
	if (GetFlag(V) == 1)
	{
		m_uCycles++;
		m_uAddrAbs = m_uPc + m_uAddrRel;
		
		if((m_uAddrAbs & 0xFF00) != (m_uPc & 0xFF00))
        {    
            m_uCycles++;
        }
		
		m_uPc = m_uAddrAbs;
	}
	return 0;
}

uint8_t Chip6502::CLC()
{
	SetFlag(C, false);
	return 0;
}

uint8_t Chip6502::CLD()
{
	SetFlag(D, false);
	return 0;
}

uint8_t Chip6502::CLI()
{
	SetFlag(I, false);
	return 0;
}

uint8_t Chip6502::CLV()
{
	SetFlag(V, false);
	return 0;
}

uint8_t Chip6502::CMP()
{
	fetch();
	m_uTemp = (uint16_t)m_uAccumulator - (uint16_t)m_uFetched;
	SetFlag(C, m_uAccumulator >= m_uFetched);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	return 1;
}

uint8_t Chip6502::CPX()
{
	fetch();
	m_uTemp = (uint16_t)m_uX - (uint16_t)m_uFetched;
	SetFlag(C, m_uX >= m_uFetched);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	return 0;
}

uint8_t Chip6502::CPY()
{
	fetch();
	m_uTemp = (uint16_t)m_uY - (uint16_t)m_uFetched;
	SetFlag(C, m_uY >= m_uFetched);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	return 0;
}

uint8_t Chip6502::DEC()
{
	fetch();
	m_uTemp = m_uFetched - 1;
	write(m_uAddrAbs, m_uTemp & 0x00FF);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	return 0;
}

uint8_t Chip6502::DEX()
{
	m_uX--;
	SetFlag(Z, m_uX == 0x00);
	SetFlag(N, m_uX & 0x80);
	return 0;
}

uint8_t Chip6502::DEY()
{
	m_uY--;
	SetFlag(Z, m_uY == 0x00);
	SetFlag(N, m_uY & 0x80);
	return 0;
}

uint8_t Chip6502::EOR()
{
	fetch();
	m_uAccumulator = m_uAccumulator ^ m_uFetched;	
	SetFlag(Z, m_uAccumulator == 0x00);
	SetFlag(N, m_uAccumulator & 0x80);
	return 1;
}

uint8_t Chip6502::INC()
{
	fetch();
	m_uTemp = m_uFetched + 1;
	write(m_uAddrAbs, m_uTemp & 0x00FF);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	return 0;
}

uint8_t Chip6502::INX()
{
	m_uX++;
	SetFlag(Z, m_uX == 0x00);
	SetFlag(N, m_uX & 0x80);
	return 0;
}

uint8_t Chip6502::INY()
{
	m_uY++;
	SetFlag(Z, m_uY == 0x00);
	SetFlag(N, m_uY & 0x80);
	return 0;
}

uint8_t Chip6502::JMP()
{
	m_uPc = m_uAddrAbs;
	return 0;
}

uint8_t Chip6502::JSR()
{
	m_uPc--;

	write(0x0100 + m_uStkp, (m_uPc >> 8) & 0x00FF);
	m_uStkp--;
	write(0x0100 + m_uStkp, m_uPc & 0x00FF);
	m_uStkp--;

	m_uPc = m_uAddrAbs;
	return 0;
}

uint8_t Chip6502::LDA()
{
	fetch();
	m_uAccumulator = m_uFetched;
	SetFlag(Z, m_uAccumulator == 0x00);
	SetFlag(N, m_uAccumulator & 0x80);
	return 1;
}

uint8_t Chip6502::LDX()
{
	fetch();
	m_uX = m_uFetched;
	SetFlag(Z, m_uX == 0x00);
	SetFlag(N, m_uX & 0x80);
	return 1;
}

uint8_t Chip6502::LDY()
{
	fetch();
	m_uY = m_uFetched;
	SetFlag(Z, m_uY == 0x00);
	SetFlag(N, m_uY & 0x80);
	return 1;
}

uint8_t Chip6502::LSR()
{
	fetch();
	SetFlag(C, m_uFetched & 0x0001);
	m_uTemp = m_uFetched >> 1;	
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IMP)
    {
		m_uAccumulator = m_uTemp & 0x00FF;
    }
	else
    {
		write(m_uAddrAbs, m_uTemp & 0x00FF);
    }
	return 0;
}

uint8_t Chip6502::NOP()
{
	switch (m_uOpcode) 
    {
		case 0x1C:
		case 0x3C:
		case 0x5C:
		case 0x7C:
		case 0xDC:
		case 0xFC:
			return 1;
			break;
	}
	return 0;
}

uint8_t Chip6502::ORA()
{
	fetch();
	m_uAccumulator = m_uAccumulator | m_uFetched;
	SetFlag(Z, m_uAccumulator == 0x00);
	SetFlag(N, m_uAccumulator & 0x80);
	return 1;
}

uint8_t Chip6502::PHA()
{
    write(0x0100 + m_uStkp, m_uAccumulator);
    m_uStkp--;
    return 0;
}

uint8_t Chip6502::PHP()
{
	write(0x0100 + m_uStkp, m_uStatus | B | U);
	SetFlag(B, false);
	SetFlag(U, false);
	m_uStkp--;
	return 0;
}

uint8_t Chip6502::PLA()
{
    m_uStkp++;
    m_uAccumulator = read(0x0100 + m_uStkp);
    SetFlag(Z, m_uAccumulator == 0x00);
    SetFlag(N, m_uAccumulator & 0x80);
    return 0;
}

uint8_t Chip6502::PLP()
{
	m_uStkp++;
	m_uStatus = read(0x0100 + m_uStkp);
	SetFlag(U, true);
	return 0;
}

uint8_t Chip6502::ROL()
{
	fetch();
	m_uTemp = (uint16_t)(m_uFetched << 1) | GetFlag(C);
	SetFlag(C, m_uTemp & 0xFF00);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x0000);
	SetFlag(N, m_uTemp & 0x0080);
	if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IMP)
    {
        m_uAccumulator = m_uTemp & 0x00FF;
    }
	else
    {
		write(m_uAddrAbs, m_uTemp & 0x00FF);
    }
	return 0;
}

uint8_t Chip6502::ROR()
{
	fetch();
	m_uTemp = (uint16_t)(GetFlag(C) << 7) | (m_uFetched >> 1);
	SetFlag(C, m_uFetched & 0x01);
	SetFlag(Z, (m_uTemp & 0x00FF) == 0x00);
	SetFlag(N, m_uTemp & 0x0080);
	if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IMP)
    {
        m_uAccumulator = m_uTemp & 0x00FF;
    }
	else
    {
		write(m_uAddrAbs, m_uTemp & 0x00FF);
    }
	return 0;
}

uint8_t Chip6502::RTI()
{
    m_uStkp++;
    m_uStatus = read(0x0100 + m_uStkp);
    m_uStatus &= ~B;
    m_uStatus &= ~U;

    m_uStkp++;
    m_uPc = (uint16_t)read(0x0100 + m_uStkp);
    m_uStkp++;
    m_uPc |= (uint16_t)read(0x0100 + m_uStkp) << 8;
    return 0;
}

uint8_t Chip6502::RTS()
{
	m_uStkp++;
	m_uPc = (uint16_t)read(0x0100 + m_uStkp);
	m_uStkp++;
	m_uPc |= (uint16_t)read(0x0100 + m_uStkp) << 8;
	
	m_uPc++;
	return 0;
}

uint8_t Chip6502::SEC()
{
	SetFlag(C, true);
	return 0;
}

uint8_t Chip6502::SED()
{
	SetFlag(D, true);
	return 0;
}

uint8_t Chip6502::SEI()
{
	SetFlag(I, true);
	return 0;
}

uint8_t Chip6502::STA()
{
	write(m_uAddrAbs, m_uAccumulator);
	return 0;
}

uint8_t Chip6502::STX()
{
	write(m_uAddrAbs, m_uX);
	return 0;
}

uint8_t Chip6502::STY()
{
	write(m_uAddrAbs, m_uY);
	return 0;
}

uint8_t Chip6502::TAX()
{
	m_uX = m_uAccumulator;
	SetFlag(Z, m_uX == 0x00);
	SetFlag(N, m_uX & 0x80);
	return 0;
}

uint8_t Chip6502::TAY()
{
	m_uY = m_uAccumulator;
	SetFlag(Z, m_uY == 0x00);
	SetFlag(N, m_uY & 0x80);
	return 0;
}

uint8_t Chip6502::TSX()
{
	m_uX = m_uStkp;
	SetFlag(Z, m_uX == 0x00);
	SetFlag(N, m_uX & 0x80);
	return 0;
}

uint8_t Chip6502::TXA()
{
	m_uAccumulator = m_uX;
	SetFlag(Z, m_uAccumulator == 0x00);
	SetFlag(N, m_uAccumulator & 0x80);
	return 0;
}

uint8_t Chip6502::TXS()
{
	m_uStkp = m_uX;
	return 0;
}

uint8_t Chip6502::TYA()
{
	m_uAccumulator = m_uY;
	SetFlag(Z, m_uAccumulator == 0x00);
	SetFlag(N, m_uAccumulator & 0x80);
	return 0;
}

uint8_t Chip6502::XXX()
{
	return 0;
}

// CPU Functions

// void Chip6502::clock()
// {
//     if (m_uCycles == 0)
//     {
//         m_uOpcode = read(m_uPc);
//         m_uPc++;
//         m_uCycles = m_vLookup[m_uOpcode].cycles;

//         uint8_t additional_cycle1 = (this->*m_vLookup[m_uOpcode].addrMode)();
//         uint8_t additional_cycle2 = (this->*m_vLookup[m_uOpcode].operate)();

//         m_uCycles += (additional_cycle1 & additional_cycle2);
//     }
//     m_uCycles--;
// }


// Aux functions
bool Chip6502::complete()
{
	return m_uCycles == 0;
}

void Chip6502::clock()
{
	if (m_uCycles == 0)
	{
		m_uOpcode = read(m_uPc);
		SetFlag(U, true);
		m_uPc++;
		m_uCycles = m_vLookup[m_uOpcode].cycles;

		uint8_t additional_cycle1 = (this->*m_vLookup[m_uOpcode].addrMode)();
		uint8_t additional_cycle2 = (this->*m_vLookup[m_uOpcode].operate)();

		m_uCycles += (additional_cycle1 & additional_cycle2);
        
		SetFlag(U, true);
	}
    
	m_uClockCount++;
	m_uCycles--;
}

void Chip6502::reset()
{
    m_uAddrAbs = 0xFFFC;
    uint16_t lo = read(m_uAddrAbs + 0);
    uint16_t hi = read(m_uAddrAbs + 1);

    m_uPc = (hi << 8) | lo;

    m_uAccumulator = 0;
    m_uX = 0;
    m_uY = 0;
    m_uStkp = 0xFD;
    m_uStatus = 0x00 | U;

    m_uFetched = 0x00;
    m_uCycles = RESET_CYCLES;
}

void Chip6502::irq()
{
    if (GetFlag(I) == 0)
    {
        write(0x0100 + m_uStkp, (m_uPc >> 8) & 0x00FF);
        m_uStkp--;
        write(0x0100 + m_uStkp, m_uPc & 0x00FF);
        m_uStkp--;

        SetFlag(B, false);
        SetFlag(U, true);
        SetFlag(I, true);
        write(0x0100 + m_uStkp, m_uStatus);
        m_uStkp--;

        m_uAddrAbs= 0xFFFE;
        uint16_t lo = read(m_uAddrAbs + 0);
        uint16_t hi = read(m_uAddrAbs + 1);

        m_uPc = (hi << 8) | lo;
        m_uCycles = 7;

    }
}

void Chip6502::nmi()
{
    write(0x0100 + m_uStkp, (m_uPc >> 8) & 0x00FF);
    m_uStkp--;
    write(0x0100 + m_uStkp, m_uPc & 0x00FF);
    m_uStkp--;

    SetFlag(B, false);
    SetFlag(U, true);
    SetFlag(I, true);
    write(0x0100 + m_uStkp, m_uStatus);
    m_uStkp--;

    m_uAddrAbs= 0xFFFA;
    uint16_t lo = read(m_uAddrAbs + 0);
    uint16_t hi = read(m_uAddrAbs + 1);

    m_uPc = (hi << 8) | lo;
    m_uCycles = 8;
}

// READ/WRITE Functions
uint8_t Chip6502::read(uint16_t addr)
{
    return m_pBus->cpuRead(addr, false);
}

void Chip6502::write(uint16_t addr, uint8_t data)
{
    m_pBus->cpuWrite(addr, data);
}

// Flags
uint8_t Chip6502::GetFlag(FLAGS6502 fFlag)
{
	return ((m_uStatus & fFlag) > 0) ? 1 : 0;
}

void Chip6502::SetFlag(FLAGS6502 fFlag, bool bValue)
{
    if (bValue)
    {
        m_uStatus |= fFlag;
    }
    else
    {
        m_uStatus &= ~fFlag;
    }
}


std::map<uint16_t, std::string> Chip6502::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		std::string sInst = "$" + hex(addr, 4) + ": ";

		uint8_t m_uOpcode = m_pBus->cpuRead(addr, true); addr++;
		sInst += m_vLookup[m_uOpcode].name + " ";

		if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IMP)
		{
			sInst += " {IMP}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IMM)
		{
			value = m_pBus->cpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::ZP0)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::ZPX)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::ZPY)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IZX)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IZY)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::ABS)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = m_pBus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::ABX)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = m_pBus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::ABY)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = m_pBus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::IND)
		{
			lo = m_pBus->cpuRead(addr, true); addr++;
			hi = m_pBus->cpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (m_vLookup[m_uOpcode].addrMode == &Chip6502::REL)
		{
			value = m_pBus->cpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		mapLines[line_addr] = sInst;
	}

	return mapLines;
}