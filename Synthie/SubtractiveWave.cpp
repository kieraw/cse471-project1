#include "stdafx.h"
#include "SubtractiveWave.h"
#include <cmath>

CSubtractiveWave::CSubtractiveWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


CSubtractiveWave::~CSubtractiveWave()
{
}

void CSubtractiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}

bool CSubtractiveWave::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];
	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}

void CSubtractiveWave::SetWavetables()
{
	auto table_size = GetSampleRate();
	m_wavetable.resize(table_size);

	for (auto i = 0; i < table_size; i++, m_time += 1. / GetSampleRate()){
		double sample = 0.0;
		if (m_wave_type == L"Sawtooth"){
			//Initial sin wave
			sample = m_amp * sin(m_time * 2 * PI * m_freq);

			//Add every harmonic up to nyqist frequency
			for (double h = 2.0; h <= (GetSampleRate() / 2.0) / m_freq; h++){
				sample += (m_amp / h) * sin(m_time * 2 * PI  * m_freq * h);
			}
		}
		else if (m_wave_type == L"Square"){
			//Initial sin wave
			sample = m_amp * sin(m_time * 2 * PI * m_freq);

			//Add every odd harmonic up to nyqist frequency
			for (double h = 3.0; h <= (GetSampleRate() / 2.0) / m_freq; h++){
				if ((int)h % 2 == 1)
					sample += (m_amp / h) * sin(m_time * 2 * PI  * m_freq * h);
			}
		}
		else if (m_wave_type == L"Triangle"){
			int alternatingSign = -1;
			//Initial sin wave
			sample = m_amp * sin(m_time * 2 * PI * m_freq);

			//Add every odd harmonic up to nyqist frequency
			for (double h = 3.0; h <= (GetSampleRate() / 2.0) / m_freq; h++){
				if ((int)h % 2 == 1){
					sample += (alternatingSign * m_amp / (h*h)) * sin(m_time * 2 * PI  * m_freq * h);
					alternatingSign = -alternatingSign;
				}
			}
		}

		//Implement Reson***

		//Implement Filter envelope***

		m_wavetable[i] = sample;

	}
}