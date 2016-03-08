/**
* \file AdditiveInstrument.cpp
*
* \author Kiera Wheatley
*
* \brief adding together sinusoids to make a sound
*	implements vibrato and cross fade
*/


#include "stdafx.h"
#include "AdditiveWave.h"


CAdditiveWave::CAdditiveWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440; // ??
}


CAdditiveWave::~CAdditiveWave()
{
}


void CAdditiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}


bool CAdditiveWave::Generate()
{
	return false;
}


void CAdditiveWave::SetWavetables()
{

}
