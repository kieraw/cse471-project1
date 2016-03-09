/**
* \file AmpFilter.cpp
*
* \author Kiera Wheatley
*
* \brief changes amplitude of source wave
*/

#include "stdafx.h"
#include "AmpFilter.h"
#include "Envelope.h"


CAmpFilter::CAmpFilter()
{
}


CAmpFilter::~CAmpFilter()
{
}


void CAmpFilter::Start()
{
	m_time = 0;

	m_envelope->SetDuration(m_duration);
	m_envelope->SetSampleRate(GetSampleRate());
	m_envelope->Start();
}


bool CAmpFilter::Generate()
{
	auto amplitude_factor = m_envelope->GetEnvelopeLevel();

	m_frame[0] = amplitude_factor * m_source->Frame(0);
	m_frame[1] = amplitude_factor * m_source->Frame(1);

	m_time += GetSamplePeriod();
	return m_duration > m_time;
}
