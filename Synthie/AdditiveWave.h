/**
* \file AdditiveWave.h
*
* \author Kiera Wheatley
*
* \brief wave for additive instrument
*	implements vibrato and cross fade
*/

#pragma once
#include "SampleWave.h"

using namespace std;

class CAdditiveWave :
	public CSampleWave
{
public:
	CAdditiveWave();
	virtual ~CAdditiveWave();

	void Start();
	bool Generate();

	void AddHarmonic(double harmonic) { m_harmonics.push_back(harmonic); }

	// GETTERS
	vector<double> GetHarmonics() { return m_harmonics; }
	bool GetVibratoFlag() { return m_implement_vibrato; }
	bool GetCrossfadeFlag() { return m_implement_crossfade; }
	double GetCrossfadeStartTime() { return m_crossfade_start_time; }

	// SETTERS
	void SetWavetables();
	void SetVibratoFlag(bool flag) { m_implement_vibrato = flag; }
	void SetCrossfadeFlag(bool flag) { m_implement_crossfade = flag; }
	void SetCrossfadeStartTime(double time) { m_crossfade_start_time = time; }

private:
	// need the harmonics
	vector<double> m_harmonics;
	// keep track of time
	double m_time;
	// vibrato?
	bool m_implement_vibrato = false;
	// cross fade?
	bool m_implement_crossfade = false;
	// when to begin the cross fade
	double m_crossfade_start_time;
};

