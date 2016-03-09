/**
* \file Envelope.h
*
* \author Kiera Wheatley
*
* \brief base class for the envelopes
*/

#pragma once
#include "AudioNode.h"

class CEnvelope :
	public CAudioNode
{
public:
	CEnvelope();
	virtual ~CEnvelope();

	virtual void Start() override {};
	virtual bool Generate() override { return false; }

	// GETTERS
	double GetEnvelopeLevel() { return m_level; }

	// SETTERS
	void SetDuration(double d) { m_duration = d; }

protected:
	double m_duration;
	double m_time;
	double m_level;
};

