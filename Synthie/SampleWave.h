/**
* \file SampleWave.h
*
* \author Kiera Wheatley
*
* \brief base class for waves in a sample
*/

#pragma once
#include "AudioNode.h"
#include <vector>

class CSampleWave :
	public CAudioNode
{
public:
	CSampleWave();
	virtual ~CSampleWave();

	// GETTERS

	// get the size of the wave table
	double GetWavetableSize() { return mWavetable.size(); }
	// get the frequency
	double GetFreq() { return m_freq; }
	// get the amplitude
	double GetAmp() { return m_amp; }
	// get the phase
	double GetPhase() { return m_phase; }
	// get the filter
	bool GetFilter() { return m_filter; }

	// SETTERS

	// sets the frequency
	void SetFreq(double f) { m_freq = f; }
	// sets the amplitude
	void SetAmp(double a) { m_amp = a; }
	// sets the wave tables
	virtual void SetWavetables() = 0;

protected:
	std::vector<double> mWavetable;  // wave table
	double m_freq; // frequency
	double m_amp;  // amplitude
	double m_phase;  // phase
	bool m_filter;  // filter
};

