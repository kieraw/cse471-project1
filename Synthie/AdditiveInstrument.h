/**
* \file AdditiveInstrument.h
*
* \author Kiera Wheatley
*
* \brief adding together sinusoids to make a sound
*	implements vibrato and cross fade
*/

#pragma once
#include "Instrument.h"
#include "AdditiveWave.h"

#include <list>

using namespace std;

class CAdditiveInstrument :
	public CInstrument
{
public:
	CAdditiveInstrument();
	virtual ~CAdditiveInstrument();
	CAdditiveInstrument(double bpm);

	void Start();
	bool Generate();

	void AddHarmonics(std::wstring harmonics);

	// SETTERS
	void SetNote(CNote *note);
	void SetFreq(double freq) { m_additive_wave.SetFreq(freq); }
	void SetAmplitude(double amp) { m_additive_wave.SetAmp(amp); }
	void SetDuration(double d) { m_duration = d; }

private:
	double m_duration;
	double m_time;
	double m_crossfade_duration = 0;
	CAdditiveWave m_additive_wave;
	CAdditiveInstrument* m_next = nullptr;
};
