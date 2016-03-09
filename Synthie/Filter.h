/**
* \file Filter.h
*
* \author Kiera Wheatley
*
* \brief base class for filters
*/

#pragma once
#include "AudioNode.h"

class CEnvelope;

class CFilter :
	public CAudioNode
{
public:
	CFilter();
	virtual ~CFilter();

	// SETTERS
	void SetEnvelope(CEnvelope* envelope) { m_envelope = envelope; }
	void SetSource(CAudioNode* source) { m_source = source; }
	void SetDuration(double duration) { m_duration = duration; }

protected:
	CAudioNode* m_source;
	CEnvelope* m_envelope;
	double m_duration;
	double m_time;
};

