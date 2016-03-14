#include "stdafx.h"
#include "ReverberationEffect.h"


CReverberationEffect::CReverberationEffect()
{
}


CReverberationEffect::~CReverberationEffect()
{
}

void CReverberationEffect::Process(double* input, double* output)
{
	/*for (int c = 0; c<2; c++)
	{
		mQueue[mWrloc + c] = input[c];
		output[c] = mDry * input[c] + mWet * mQueue[(mRdloc + c) % MAXQUEUESIZE];
	}


	mWrloc = (mWrloc + 2) % MAXQUEUESIZE;
	mRdloc = (mRdloc + 2) % MAXQUEUESIZE;*/

}

void CReverberationEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
}

bool CReverberationEffect::Generate()
{
	return true;
}