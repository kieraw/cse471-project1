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

	// used for implementing the Vibrato effect
	struct Vibrato
	{
		double vibrato = 0;
		double vibrato_rate = 0;
	};

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetWavetables() override;

	void AddHarmonic(double harmonic) { m_harmonics.push_back(harmonic); }
	void ImplementHarmonics(double* sample, double time);
	void ImplementVibrato(double* sine_rads, double* vibrato_rads);
	void GenerateCrossfade(double time, double crossfade_dur);

	// GETTERS

	vector<double> GetHarmonics() { return m_harmonics; }
	bool GetVibratoFlag() { return m_implement_vibrato; }
	bool GetCrossfadeFlag() { return m_implement_crossfade; }
	double GetCrossfadeStartTime() { return m_crossfade_start_time; }

	// SETTERS

	// cross fade stuff
	void SetCrossfadeFlag(bool flag) { m_implement_crossfade = flag; }
	void SetCrossfadeStartTime(double time) { m_crossfade_start_time = time; }
	// vibrato stuff
	void SetVibratoFlag(bool flag) { m_implement_vibrato = flag; }
	void SetVibrato(double vibrato) { m_vibrato_effect.vibrato = vibrato; }
	void SetVibratoRate(double vibrato_rate) { m_vibrato_effect.vibrato_rate = vibrato_rate; }
	// wave stuff
	void SetNextWave(CAdditiveWave* next) { m_next_wave = next; }

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
	// the vibrato effect struct object
	Vibrato m_vibrato_effect;
	// the wave next to the current wave
	CAdditiveWave* m_next_wave = nullptr;
};

