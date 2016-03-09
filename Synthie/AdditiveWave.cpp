/**
* \file AdditiveWave.cpp
*
* \author Kiera Wheatley
*
* \brief wave for additive instrument
*	implements vibrato and cross fade
*/


#include "stdafx.h"
#include "AdditiveWave.h"
#include <cmath>


CAdditiveWave::CAdditiveWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


CAdditiveWave::~CAdditiveWave()
{
}


void CAdditiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}


bool CAdditiveWave::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];
	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}


void CAdditiveWave::SetWavetables()
{
	auto table_size = GetSampleRate();
	m_wavetable.resize(table_size);

	// sine and vibrato radians
	double sine_rads = 0;
	double vibrato_rads = 0;

	for (auto i = 0; i < table_size; i++, m_time += 1. / GetSampleRate())
	{
		auto sample = sin(sine_rads) * m_amp;

		// harmonics
		if (m_harmonics.size() > 0)
		{
			ImplementHarmonics(&sample, m_time);
		}

		// check for vibrato effect
		if (m_implement_vibrato)
		{
			ImplementVibrato(&sine_rads, &vibrato_rads);
		}

		m_wavetable[i] = sample;
	}
}


void CAdditiveWave::ImplementHarmonics(double* sample, double time)
{
	// Nyquist Frequency
	auto nyquist_freq = GetSampleRate() / 2;

	for (auto x = 0; x < m_harmonics.size() && (m_freq * (x + 1)) < nyquist_freq; x++)
	{
		// adjust to match the harmonic number
		auto harmonic = x + 1;

		// save value of sample in memory to be used at end of SetWavetables()
		*sample += m_harmonics[x] * (m_amp / harmonic) * (sin(time * 2 * PI * harmonic * m_freq));
	}
}


void CAdditiveWave::GenerateCrossfade(double time, double crossfade_dur)
{
	auto elapsed_time = time - m_crossfade_start_time;


}


void CAdditiveWave::ImplementVibrato(double* sine_rads, double* vibrato_rads)
{
	
}