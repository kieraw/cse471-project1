#pragma once
#include "PianoInstrument.h"

class CPianoInstrumentFactory
{
public:
	CPianoInstrumentFactory();
	virtual ~CPianoInstrumentFactory();

	CPianoInstrument *CreateInstrument();
	void SetNote(CNote *note);

private:
	double m_duration;
	double m_volume;
	bool m_pedal;
};

