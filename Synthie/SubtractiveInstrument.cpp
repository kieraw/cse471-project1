#include "stdafx.h"
#include "SubtractiveInstrument.h"


CSubtractiveInstrument::CSubtractiveInstrument()
{
	m_duration = 0.1;
}


CSubtractiveInstrument::~CSubtractiveInstrument()
{
}
CSubtractiveInstrument::CSubtractiveInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}
void CSubtractiveInstrument::SetNote(CNote *note)
{
}

void CSubtractiveInstrument::Start()
{
	// set the sample rate of the wave
	mSubtractiveWave.SetSampleRate(GetSampleRate());
	mSubtractiveWave.Start();
	m_time = 0;
}
bool CSubtractiveInstrument::Generate()
{
	return false;
}


