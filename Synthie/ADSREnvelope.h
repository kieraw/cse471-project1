/**
* \file ADSREnvelope.h
*
* \author Kiera Wheatley
*
* \brief ADSR - attack, decay, sustain, release
*/

#pragma once
#include "Envelope.h"

class CADSREnvelope :
	public CEnvelope
{
public:
	CADSREnvelope();
	virtual ~CADSREnvelope();

	virtual void Start() override;
	virtual bool Generate() override;

	// SETTERS
	void SetAttack(double attack) { m_attack = attack; }
	void SetDecay(double decay) { m_decay = decay; }
	void SetSustain(double sustain) { m_sustain = sustain; }
	void SetRelease(double release) { m_release = release; }

private:
	// ADSR
	double m_attack;
	double m_decay;
	double m_sustain; // sustain level
	double m_release;
};

