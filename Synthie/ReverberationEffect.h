#pragma once
#include "AudioEffect.h"
class CReverberationEffect :
	public CAudioEffect
{
public:
	CReverberationEffect();
	virtual ~CReverberationEffect();

	virtual void Process(double *input, double *output) override;

	virtual void Start() override;

	virtual bool Generate() override;
};

