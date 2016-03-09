#pragma once
#include "SampleWave.h"
using namespace std;

class CSubtractiveWave :
	public CSampleWave
{
public:
	CSubtractiveWave();
	~CSubtractiveWave();

	void Start();
	bool Generate();

	void AddHarmonic(double harmonic) { m_harmonics.push_back(harmonic); }

	//Getters
	vector<double> GetHarmonics() { return m_harmonics; }

	//Setters
	void SetWaveType(wstring type){ m_wave_type = type; }
	void SetWavetables();

private:
	wstring m_wave_type; //square, sawtooth, triange?
	// need the harmonics
	vector<double> m_harmonics;
	// keep track of time
	double m_time;
};

