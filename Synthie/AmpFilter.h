/**
* \file AmpFilter.h
*
* \author Kiera Wheatley
*
* \brief changes amplitude of source wave
*/

#pragma once
#include "Filter.h"

class CAmpFilter :
	public CFilter
{
public:
	CAmpFilter();
	virtual ~CAmpFilter();

	virtual void Start() override;
	virtual bool Generate() override;
};

