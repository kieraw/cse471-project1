#include "stdafx.h"
#include "SubtractiveWave.h"


CSubtractiveWave::CSubtractiveWave()
{
}


CSubtractiveWave::~CSubtractiveWave()
{
}

void CSubtractiveWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}

bool CSubtractiveWave::Generate()
{
	return false;
}

void CSubtractiveWave::SetWavetables()
{

}