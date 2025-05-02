#pragma once

#include <cstdint>
#include <functional>
#include <math.h>




class chip2A03
{
public:
    chip2A03();
    virtual ~chip2A03();

public:
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr);
    void clock();
    void reset();
    double GetOutputSample();

private:
    uint32_t frame_clock_counter = 0;
    uint32_t clock_counter = 0;
	bool m_bUseRawMode = false;

    static uint8_t length_table[];

    struct sequencer
    {
        uint32_t sequence = 0x00000000;
		uint32_t new_sequence = 0x00000000;
        uint16_t timer = 0x0000;
        uint16_t reload = 0x0000;
        uint8_t output = 0x00;

        uint8_t clock(bool bEnable, std::function<void(uint32_t &s)> funcManip)
        {
            if (bEnable)
            {
                timer--;
                if (timer == 0xFFFF)
                {
                    timer = reload + 1;
                    funcManip(sequence);
                    output = sequence & 0x00000001;
                }
            }
            return output;
        }
    };

    struct lengthcounter
	{
		uint8_t counter = 0x00;
		uint8_t clock(bool bEnable, bool bHalt)
		{
			if (!bEnable)
				counter = 0;
			else
				if (counter > 0 && !bHalt)
					counter--;
			return counter;
		}
	};

    struct envelope
	{
		void clock(bool bLoop)
		{
			if (!start)
			{
				if (divider_count == 0)
				{
					divider_count = volume;

					if (decay_count == 0)
					{
						if (bLoop)
						{
							decay_count = 15;
						}

					}
					else
						decay_count--;
				}
				else
					divider_count--;
			}
			else
			{
				start = false;
				decay_count = 15;
				divider_count = volume;
			}

			if (disable)
			{
				output = volume;
			}
			else
			{
				output = decay_count;
			}
		}

		bool start = false;
		bool disable = false;
		uint16_t divider_count = 0;
		uint16_t volume = 0;
		uint16_t output = 0;
		uint16_t decay_count = 0;
	};

    struct oscpulse
    {
        double frequency = 0;
        double dutycycle = 0;
        double amplitude = 1;
        double pi = 3.14159f;
        double harmonics = 20;

        double sample(double t)
        {
            double a = 0;
            double b = 0;
            double p = dutycycle*2.0*pi;

            auto approxSin = [](double t)
			{
				double j = t * 0.15915;
				j = j - (int)j;
				return 20.785 * j * (j - 0.5) * (j - 1.0);
			};

            for (double n = 1; n < harmonics; n++)
            {
                double c = n * frequency * 2.0 * pi * t;
                a += -approxSin(c) / n;
                b += -approxSin(c - (p*n)) / n;
            }
            return (2.0 * amplitude / pi) * (a - b);
        }
    };

    struct sweeper
	{
		bool enabled = false;
		bool down = false;
		bool reload = false;
		uint8_t shift = 0x00;
		uint8_t timer = 0x00;
		uint8_t period = 0x00;
		uint16_t change = 0;
		bool mute = false;

		void track(uint16_t &target)
		{
			if (enabled)
			{
				change = target >> shift;
				mute = (target < 8) || (target > 0x7FF);
			}
		}

		bool clock(uint16_t &target, bool channel)
		{
			bool changed = false;
			if (timer == 0 && enabled && shift > 0 && !mute)
			{
				if (target >= 8 && change < 0x07FF)
				{
					if (down)
					{
						target -= change - channel;
					}
					else
					{
						target += change;
					}
					changed = true;
				}
			}

			//if (enabled)
			{
				if (timer == 0 || reload)
				{
					timer = period;
					reload = false;
				}
				else
					timer--;

				mute = (target < 8) || (target > 0x7FF);
			}

			return changed;
		}
	};

    double m_dGlobalTime = 0.0;

    bool m_bPulse1Enable = false;
    bool m_bPulse1Halt = false;
    double m_dPulse1Sample = 0.0;
    double m_dPulse1Output = 0.0;

    sequencer m_sPulse1Seq;
    oscpulse m_sPulse1Osc;
    envelope m_sPulse1Env;
    lengthcounter m_sPulse1LC;
    sweeper m_sPulse1Sweep;

    bool m_bPulse2Enable = false;
    bool m_bPulse2Halt = false;
    double m_dPulse2Sample = 0.0;
    double m_dPulse2Output = 0.0;

    sequencer m_sPulse2Seq;
    oscpulse m_sPulse2Osc;
    envelope m_sPulse2Env;
    lengthcounter m_sPulse2LC;
    sweeper m_sPulse2Sweep;

    bool m_bNoiseEnable = false;
    bool m_bNoiseHalt = false;
    double m_dNoiseSample = 0.0;
    double m_dNoiseOutput = 0.0;
    envelope m_sNoiseEnv;
    lengthcounter m_sNoiseLC;
    sequencer m_sNoiseSeq;

public:
    uint16_t m_nPulse1Visual;
    uint16_t m_nPulse2Visual;
    uint16_t m_nNoiseVisual;
    uint16_t m_nTriangleVisual;
};