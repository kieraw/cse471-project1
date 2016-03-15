#include "stdafx.h"
#include "FlangeEffect.h"


CFlangeEffect::CFlangeEffect()
{
}


CFlangeEffect::~CFlangeEffect()
{
}

void CFlangeEffect::Process(double* input, double* output)
{
	double delayVariance = (RANGE * mDelay) * sin(2 * PI * RATE);
	double newDelay = mDelay + delayVariance;

	mWrloc = (mWrloc + 1) % 200000;
	m_queueL[mWrloc + newDelay] = input[0];
	mWrloc = (mWrloc + 1) % 200000;
	m_queueR[mWrloc + newDelay] = input[1];

	int delayLength = int((newDelay * m_sampleRate + 0.5)) * 2;
	int rdloc = (mWrloc + 200000 - delayLength) % 200000;

	// Wet
	output[0] = input[0] / 3 + m_queueL[rdloc] / 3 + (mOutL[rdloc] * LEVEL) / 3;
	output[0] *= mWet;
	output[1] = input[1] / 3 + m_queueR[(rdloc + 1) % 200000] / 3 + (mOutR[(rdloc + 1) % 200000] * LEVEL) / 3;
	output[1] *= mWet;

	// Dry
	output[0] += input[0] * mDry;
	output[1] += input[1] * mDry;

	mOutL[mWrloc] = output[0];
	mOutR[mWrloc] = output[1];
}

void CFlangeEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	mOutL.resize(200000);
	mOutR.resize(200000);
}

bool CFlangeEffect::Generate()
{
	return true;
}