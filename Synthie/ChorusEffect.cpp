#include "stdafx.h"
#include "ChorusEffect.h"


CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}


void CChorusEffect::Process(double* input, double* output)
{

	double delayVariance = (RANGE * mDelay) * sin(2 * PI * RATE);
	double newDelay = mDelay + delayVariance;

	mWrloc = (mWrloc + 1) % 200000;
	m_queueL[mWrloc] = input[0];
	m_queueR[mWrloc] = input[1];

	int delayLength = int((newDelay * GetSampleRate() + 0.5)) * 2;
	int rdloc = (mWrloc + 200000 - delayLength) % 200000;

	// Wet
	output[0] = input[0] / 2 + m_queueL[rdloc] / 2;
	output[0] *= mWet;
	output[1] = input[1] / 2 + m_queueR[rdloc] / 2;
	output[1] *= mWet;

	// Dry
	output[0] += input[0] * mDry;
	output[1] += input[1] * mDry;

}

void CChorusEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
}

bool CChorusEffect::Generate()
{
	return true;
}