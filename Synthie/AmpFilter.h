/**
* \file AmpFilter.h
*
* \author Kiera Wheatley
*
* \brief changes amplitude of source wave
*/

#pragma once
#include "AudioFilter.h"

class CAmpFilter :
	public CAudioFilter
{
public:
	CAmpFilter();
	virtual ~CAmpFilter();

	virtual void Start() override;
	virtual bool Generate() override;
};

