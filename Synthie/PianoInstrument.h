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
	void ChangeDuration();
	void Envelope();
	bool LoadFile(const char *filename);

	void SetPedal(bool pedal){ m_pedal = pedal; }
	void SetVolume(double vol){ m_volume = vol; }

	bool PlayPedalDown();
	bool PlayPedalUp();

	CWavePlayer *GetPlayer() { return &m_wavePlayer; }

private:
	CWavePlayer m_wavePlayer;
	std::vector<short> m_wave;
	std::vector<short> m_pedalWave;
	double m_duration;
	double m_time;
	double m_attack;
	double m_release;
	double m_volume; // a value of 1.0 is default. Larger==Louder, smaller==softer
	bool m_pedal;
	CCAR m_ar;
};

