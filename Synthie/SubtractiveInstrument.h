#pragma once
#include "Instrument.h"
#include "SubtractiveWave.h"
class CSubtractiveInstrument :
	public CInstrument
{
public:
	CSubtractiveInstrument();
	~CSubtractiveInstrument();
	CSubtractiveInstrument(double bpm);

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note) override;

	//Setters
	void SetFreq(double freq) { mSubtractiveWave.SetFreq(freq); }
	void SetAmplitude(double amp) { mSubtractiveWave.SetAmp(amp); }
	void SetDuration(double d) { m_duration = d; }

private:
	double m_duration;
	double m_time;
	CSubtractiveWave mSubtractiveWave;


};

