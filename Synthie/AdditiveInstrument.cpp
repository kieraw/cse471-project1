/**
* \file AdditiveInstrument.cpp
*
* \author Kiera Wheatley
*
* \brief adding together sinusoids to make a sound
*	implements vibrato and cross fade
*/


#include "stdafx.h"
#include "AdditiveInstrument.h"
#include "Note.h"
#include "Notes.h"
#include "Envelope.h"
#include "ADSREnvelope.h"


CAdditiveInstrument::CAdditiveInstrument()
{
	m_duration = 0.1;
}


CAdditiveInstrument::CAdditiveInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}


CAdditiveInstrument::~CAdditiveInstrument()
{
}


void CAdditiveInstrument::Start()
{
	// set the sample rate of the wave
	m_additive_wave.SetSampleRate(GetSampleRate());
	m_additive_wave.Start();
	m_time = 0;

	m_envelope = new CADSREnvelope();
	static_cast<CADSREnvelope*>(m_envelope)->SetAttack(.05);
	static_cast<CADSREnvelope*>(m_envelope)->SetRelease(.05);

	m_amp_filter.SetEnvelope(m_envelope);
	m_amp_filter.SetSource(&m_additive_wave);
	m_amp_filter.SetSampleRate(GetSampleRate());
	m_amp_filter.SetDuration(m_duration);
	m_amp_filter.Start();
}


bool CAdditiveInstrument::Generate()
{
	// m_envelope->Generate();

	return true;
}


void CAdditiveInstrument::SetNote(CNote *note)
{

}


void CAdditiveInstrument::SetNextNote(CNote* next_note)
{

}


void CAdditiveInstrument::AddHarmonics(wstring harmonics)
{

}