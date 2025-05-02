#include "chip2A03.h"

uint8_t chip2A03::length_table[] = {  10, 254, 20,  2, 40,  4, 80,  6,
    160,   8, 60, 10, 14, 12, 26, 14,
     12,  16, 24, 18, 48, 20, 96, 22,
    192,  24, 72, 26, 16, 28, 32, 30 };

chip2A03::chip2A03()
{

}

chip2A03::~chip2A03()
{
    
}

void chip2A03::cpuWrite(uint16_t addr, uint8_t data)
{
    switch(addr)
    {
        case 0x4000:
            switch ((data & 0xC0) >> 6)
            {
                case 0x00:
                    m_sPulse1Seq.new_sequence = 0b00000001;
                    m_sPulse1Osc.dutycycle = 0.125;
                    break;
                
                case 0x01:
                    m_sPulse1Seq.new_sequence = 0b00000011;
                    m_sPulse1Osc.dutycycle = 0.250;
                    break;
            
                case 0x02:
                    m_sPulse1Seq.new_sequence = 0b00001111;
                    m_sPulse1Osc.dutycycle = 0.500;
                    break;
            
                case 0x03:
                    m_sPulse1Seq.new_sequence = 0b11111100; 
                    m_sPulse1Osc.dutycycle = 0.750;
                    break;
                
                default:
                    break;
            }
            m_sPulse1Seq.sequence = m_sPulse1Seq.new_sequence;
            m_bPulse1Halt = (data & 0x20);
            m_sPulse1Env.volume = (data & 0x0F);
            m_sPulse1Env.disable = (data & 0x10);
            break;
        case 0x4001:
            m_sPulse1Sweep.enabled = data & 0x80;
            m_sPulse1Sweep.period = (data & 0x70) >> 4;
            m_sPulse1Sweep.down = data & 0x08;
            m_sPulse1Sweep.shift = data & 0x07;
            m_sPulse1Sweep.reload = true;
            break;
        case 0x4002:
            m_sPulse1Seq.reload = (m_sPulse1Seq.reload & 0xFF00) | data;
            break;
        case 0x4003:
            m_sPulse1Seq.reload = (uint16_t)((data & 0x07)) << 8 | (m_sPulse1Seq.reload & 0x00FF);
            m_sPulse1Seq.timer = m_sPulse1Seq.reload;
            m_sPulse1Seq.sequence = m_sPulse1Seq.new_sequence;
            m_sPulse1LC.counter = length_table[(data & 0xF8) >> 3];
            m_sPulse1Env.start = true;
            break;
        case 0x4004:
        switch ((data & 0xC0) >> 6)
		{
            case 0x00: m_sPulse2Seq.new_sequence = 0b01000000; m_sPulse2Osc.dutycycle = 0.125; break;
            case 0x01: m_sPulse2Seq.new_sequence = 0b01100000; m_sPulse2Osc.dutycycle = 0.250; break;
            case 0x02: m_sPulse2Seq.new_sequence = 0b01111000; m_sPulse2Osc.dutycycle = 0.500; break;
            case 0x03: m_sPulse2Seq.new_sequence = 0b10011111; m_sPulse2Osc.dutycycle = 0.750; break;
            }
            m_sPulse2Seq.sequence = m_sPulse2Seq.new_sequence;
            m_bPulse2Halt = (data & 0x20);
            m_sPulse2Env.volume = (data & 0x0F);
            m_sPulse2Env.disable = (data & 0x10);
            break;
        case 0x4005:
            m_sPulse2Sweep.enabled = data & 0x80;
            m_sPulse2Sweep.period = (data & 0x70) >> 4;
            m_sPulse2Sweep.down = data & 0x08;
            m_sPulse2Sweep.shift = data & 0x07;
            m_sPulse2Sweep.reload = true;
            break;
        case 0x4006:
            m_sPulse2Seq.reload = (m_sPulse2Seq.reload & 0xFF00) | data;
            break;
        case 0x4007:
            m_sPulse2Seq.reload = (uint16_t)((data & 0x07)) << 8 | (m_sPulse2Seq.reload & 0x00FF);
            m_sPulse2Seq.timer = m_sPulse2Seq.reload;
            m_sPulse2Seq.sequence = m_sPulse2Seq.new_sequence;
            m_sPulse2LC.counter = length_table[(data & 0xF8) >> 3];
            m_sPulse2Env.start = true;
            break;
        case 0x4008:
            break;
        case 0x400C:
            m_sNoiseEnv.volume = (data & 0x0F);
            m_sNoiseEnv.disable = (data & 0x10);
            m_bNoiseHalt = (data & 0x20);
            break;
        case 0x400E:
        switch (data & 0x0F)
		{
            case 0x00: m_sNoiseSeq.reload = 0; break;
            case 0x01: m_sNoiseSeq.reload = 4; break;
            case 0x02: m_sNoiseSeq.reload = 8; break;
            case 0x03: m_sNoiseSeq.reload = 16; break;
            case 0x04: m_sNoiseSeq.reload = 32; break;
            case 0x05: m_sNoiseSeq.reload = 64; break;
            case 0x06: m_sNoiseSeq.reload = 96; break;
            case 0x07: m_sNoiseSeq.reload = 128; break;
            case 0x08: m_sNoiseSeq.reload = 160; break;
            case 0x09: m_sNoiseSeq.reload = 202; break;
            case 0x0A: m_sNoiseSeq.reload = 254; break;
            case 0x0B: m_sNoiseSeq.reload = 380; break;
            case 0x0C: m_sNoiseSeq.reload = 508; break;
            case 0x0D: m_sNoiseSeq.reload = 1016; break;
            case 0x0E: m_sNoiseSeq.reload = 2034; break;
            case 0x0F: m_sNoiseSeq.reload = 4068; break;
		}
            break;
        case 0x400F:
            m_sPulse1Env.start = true;
            m_sPulse2Env.start = true;
            m_sNoiseEnv.start = true;
            m_sNoiseLC.counter = length_table[(data & 0xF8) >> 3];
            break;
        case 0x4015:
            m_bPulse1Enable = data & 0x01;
            m_bPulse2Enable = data & 0x02;
            m_bNoiseEnable = data & 0x04;
            break;
    }
}

uint8_t chip2A03::cpuRead(uint16_t addr)
{
    uint8_t data = 0x00;

	if (addr == 0x4015)
	{
	//	data |= (pulse1_lc.counter > 0) ? 0x01 : 0x00;
	//	data |= (pulse2_lc.counter > 0) ? 0x02 : 0x00;		
	//	data |= (noise_lc.counter > 0) ? 0x04 : 0x00;
	}

	return data;
}

void chip2A03::clock()
{
    bool bQuarterFrameClock = false;
    bool bHalfFrameClock = false;

    m_dGlobalTime += (0.3333333333 / 1789773);

    if (clock_counter % 6 == 0)
    {
        frame_clock_counter++;
        if (frame_clock_counter == 3729)
        {
            bQuarterFrameClock = true;
        }
        if (frame_clock_counter == 7457)
        {
            bQuarterFrameClock = true;
            bHalfFrameClock = true;
        }
        if (frame_clock_counter == 11186)
        {
            bQuarterFrameClock = true;
        }
        if (frame_clock_counter == 14916)
        {
            bQuarterFrameClock = true;
            bHalfFrameClock = true;
            frame_clock_counter = 0;
        }

        if (bQuarterFrameClock)
        {
            m_sPulse1Env.clock(m_bPulse1Halt);
			m_sPulse2Env.clock(m_bPulse2Halt);
			m_sNoiseEnv.clock(m_bNoiseHalt);
        }
        if (bHalfFrameClock)
        {
            m_sPulse1LC.clock(m_bPulse1Enable, m_bPulse1Halt);
			m_sPulse2LC.clock(m_bPulse2Enable, m_bPulse2Halt);
			m_sNoiseLC.clock(m_bNoiseEnable, m_bNoiseHalt);
			m_sPulse1Sweep.clock(m_sPulse1Seq.reload, 0);
			m_sPulse2Sweep.clock(m_sPulse2Seq.reload, 1);
        }
        
        m_sPulse1Seq.clock(m_bPulse1Enable, [](uint32_t &s)
            {
               s = ((s & 0x0001) << 7) | ((s & 0x00FE) >> 1); 
            }
        );
        
        m_sPulse1Osc.frequency = 1789773.0 / (16.0 * (double)(m_sPulse1Seq.reload + 1));
        m_sPulse1Osc.amplitude = (double)(m_sPulse1Env.output -1) / 16.0;
        m_dPulse1Sample = m_sPulse1Osc.sample(m_dGlobalTime);

        if (m_sPulse1LC.counter > 0 && m_sPulse1Seq.timer >= 8 && !m_sPulse1Sweep.mute && m_sPulse1Env.output > 2)
        {
            m_dPulse1Output += (m_dPulse1Sample - m_dPulse1Output) * 0.5;
        }
        else
        {
            m_dPulse1Output = 0;
        }

        m_sPulse2Seq.clock(m_bPulse2Enable, [](uint32_t &s)
            {
                s = ((s & 0x0001) << 7) | ((s & 0x00FE) >> 1);
            }
        );

        m_sPulse2Osc.frequency = 1789773.0 / (16.0 * (double)(m_sPulse2Seq.reload + 1));
        m_sPulse2Osc.amplitude = (double)(m_sPulse2Env.output-1) / 16.0;
		m_dPulse2Sample = m_sPulse2Osc.sample(m_dGlobalTime);
        if (m_sPulse2LC.counter > 0 && m_sPulse2Seq.timer >= 8 && !m_sPulse2Sweep.mute && m_sPulse2Env.output > 2)
        {
            m_dPulse2Output += (m_dPulse2Sample - m_dPulse2Output) * 0.5;
        }
        else
        {
            m_dPulse2Output = 0;
        }

        m_sNoiseSeq.clock(m_bNoiseEnable, [](uint32_t &s)
			{
				s = (((s & 0x0001) ^ ((s & 0x0002) >> 1)) << 14) | ((s & 0x7FFF) >> 1);
			}
        );

        if (m_sNoiseLC.counter > 0 && m_sNoiseSeq.timer >= 8)
		{
			m_dNoiseOutput = (double)m_sNoiseSeq.output * ((double)(m_sNoiseEnv.output-1) / 16.0);
		}

        if (!m_bPulse1Enable) m_dPulse1Output = 0;
		if (!m_bPulse2Enable) m_dPulse2Output = 0;
		if (!m_bNoiseEnable) m_dNoiseOutput = 0;

        m_sPulse1Sweep.track(m_sPulse1Seq.reload);
        m_sPulse2Sweep.track(m_sPulse2Seq.reload);

        m_nPulse1Visual = (m_bPulse1Enable && m_sPulse1Env.output > 1 && !m_sPulse1Sweep.mute) ? m_sPulse1Seq.reload : 2047;
        m_nPulse2Visual = (m_bPulse2Enable && m_sPulse2Env.output > 1 && !m_sPulse2Sweep.mute) ? m_sPulse2Seq.reload : 2047;
        m_nNoiseVisual = (m_bNoiseEnable && m_sNoiseEnv.output > 1) ? m_sNoiseSeq.reload : 2047;

    }
    clock_counter++;
}

void chip2A03::reset()
{
}

double chip2A03::GetOutputSample()
{
    if (m_bUseRawMode)
        {
            return (m_dPulse1Sample - 0.5) * 0.5
                + (m_dPulse2Sample - 0.5) * 0.5;
        }
        else
        {
            return ((1.0 * m_dPulse1Output) - 0.8) * 0.1 +
                ((1.0 * m_dPulse2Output) - 0.8) * 0.1 +
                ((2.0 * (m_dNoiseOutput - 0.5))) * 0.1;
        }
}