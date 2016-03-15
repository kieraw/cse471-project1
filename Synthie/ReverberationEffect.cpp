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
	


	mWrloc = (mWrloc + 2) % MAXQUEUESIZE;
	mRdloc = (mRdloc + 2) % MAXQUEUESIZE;

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