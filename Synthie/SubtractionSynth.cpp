#include "stdafx.h"
#include "SubtractionSynth.h"


CSubtractionSynth::CSubtractionSynth()
{
	m_duration = 0.1;
}
CSubtractionSynth::CSubtractionSynth(double bpm){
	m_duration = 0.1;
	m_bpm = bpm;
}

CSubtractionSynth::~CSubtractionSynth()
{
}


void CSubtractionSynth::Start(){
	m_sinewave.SetSampleRate(GetSampleRate());
	m_sinewave.Start();
	m_time = 0;

	// Tell the AR object it gets its samples from 
	// the sine wave object.
	m_ar.SetSource(&m_sinewave);
	m_ar.SetSampleRate(GetSampleRate());
	m_ar.Start();
}

bool CSubtractionSynth::Generate(){
	m_sinewave.Generate();
	bool valid = m_ar.Generate();

	m_frame[0] = m_ar.Frame(0);
	m_frame[1] = m_ar.Frame(1);

	m_time += GetSamplePeriod();
	return valid;
}

void CSubtractionSynth::SetNote(CNote *note){

}