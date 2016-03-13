#pragma once
#include "Instrument.h"
#include "WavePlayer.h"
#include "CAR.h"

class CPianoInstrument :
	public CInstrument
{
public:
	CPianoInstrument();
	virtual ~CPianoInstrument();

public:
	virtual void Start();
	virtual bool Generate()=0;
	//virtual void SetNote(CNote *note);
	/*void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }*/
	void SetDuration(double d) { m_duration = d; }

	CWavePlayer *GetPlayer() { return &m_wavePlayer; }

private:
	CWavePlayer m_wavePlayer;
	double m_duration;
	double m_time;
	CCAR m_ar;
};

