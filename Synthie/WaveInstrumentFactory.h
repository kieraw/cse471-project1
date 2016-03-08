#pragma once
#include "WaveInstrument.h"
#include "audio/DirSoundSource.h"
#include <vector>

class CWaveInstrumentFactory
{
public:
	CWaveInstrumentFactory(void);
	~CWaveInstrumentFactory(void);

	CWaveInstrument *CreateInstrument();
	void SetNote(CNote *note);
	bool LoadFile(const char *filename);
	void ChangePitch(double rate);
	void Glissando(double rate);

private:
	std::vector<short> m_wave;
};

