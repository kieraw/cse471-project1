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

		//Implement Reson
		if (m_implement_reson && i > 1){
			ImplementReson(&sample, i);
		}

		//Implement Filter envelope***

		m_wavetable[i] = sample;


	}
}
//Implement the Reson Filter
void CSubtractiveWave::ImplementReson(double* sample, int tableIndex){
	//Need to have at least two samples to start doing reson
	
	//Calculate reson values for reson equation
	double R = 1.0 - (m_reson_bandwidth / 2.0);
	double cosTheta = (2 * R * cos(2 * PI * m_reson_freq)) / (1 + pow(R, 2));
	double A = (1 - pow(R, 2)) * sqrt(1 - pow(cosTheta, 2));

	int prevIndex; //tableIndex - 1
	int secondPrevIndex;//tableIndex - 2

	//Set two previous table index's and loop around if need be
	if (tableIndex - 1 < 0)
		prevIndex = m_wavetable.size() - 1;
	else
		prevIndex = tableIndex - 1;
	if (tableIndex - 2 < 0)
		secondPrevIndex = m_wavetable.size() - 1;
	else
		secondPrevIndex = tableIndex - 2;

	*sample = A * *sample + (2 * R*cosTheta) * m_wavetable[prevIndex] - pow(R, 2) * m_wavetable[secondPrevIndex];


}