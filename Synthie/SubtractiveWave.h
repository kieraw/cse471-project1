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

	void ImplementReson(double* sample, int tableIndex);

	//Setters
	void SetWaveType(wstring type){ m_wave_type = type; }
	void SetReson(bool reson){ m_implement_reson = reson; }
	void SetResonFreq(double freq){ m_reson_freq = freq; }
	void SetResonBandwidth(double band){ m_reson_bandwidth = band; }
	void SetMoogSweepDown(bool flag){ m_sweep_down = flag; }
	void SetMoogSweepUp(bool flag){ m_sweep_up = flag; }
	void SetMoogSweepDownUp(bool flag){ m_sweep_down_up = flag; }
	void SetMoogSweepUpDown(bool flag){ m_sweep_up_down = flag; }
	void SetWavetables();

private:
	wstring m_wave_type; //square, sawtooth, triange?
	// keep track of time
	double m_time;
	//Apply Reson?
	bool m_implement_reson = false;
	//emphasized reson frequency, range of 0-0.5, has default value
	double m_reson_freq = 0.01134;
	//emphasized reson bandwidth, range of 0-1, has default value
	double m_reson_bandwidth = 0.01;
	//Frequency added to m_freq, which changes to similate moog
	double m_sweep_freq = 0.0;
	bool m_sweep_down = false;
	bool m_sweep_up = false;
	bool m_sweep_down_up = false;
	bool m_sweep_up_down = false;
};

