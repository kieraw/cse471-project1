#pragma once
#include "AudioNode.h"
#include "Note.h"
#include "AmpFilter.h"

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	~CInstrument();
	CInstrument(double);

	virtual void SetNote(CNote *note) = 0;

protected:
	// the amplitude filter object
	CAmpFilter m_amp_filter;
	// the envelope object
	CEnvelope* m_envelope;
};

