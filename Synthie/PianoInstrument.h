#pragma once
#include "Instrument.h"
#include "WavePlayer.h"
#include "CAR.h"
#include <vector>
#include "audio/DirSoundSource.h"

class CPianoInstrument :
	public CInstrument
{
public:
	CPianoInstrument();
	virtual ~CPianoInstrument();

public:
	virtual void Start();
	virtual bool Generate();
	virtual void SetNote(CNote *note);
	/*void SetFreq(double f) { m_sinewave.SetFreq(f); }
	void SetAmplitude(double a) { m_sinewave.SetAmplitude(a); }*/
	void SetDuration(double d) { m_duration = d; }
	bool LoadFile(const char *filename);

	CWavePlayer *GetPlayer() { return &m_wavePlayer; }

private:
	CWavePlayer m_wavePlayer;
	std::vector<short> m_wave;
	double m_duration;
	double m_time;
	CCAR m_ar;
};

