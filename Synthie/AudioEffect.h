/*
 * Base class for all effects that will be implemented. Vitrual class. 
 * All of the effects have the same variables associated with them thus the need for this class.
 * Going off of description for effects page/questions
 */

#pragma once
#include "Instrument.h"
#include <vector>
class CAudioEffect :
	public CInstrument
{
public:
	virtual ~CAudioEffect();

	virtual void Process(double *frameIn, double *frameOut) = 0;

	void SetDelay(double delay) { mDelay = delay; }

	void SetWet(double wet) { mWet = wet; }

	void SetDry(double dry) { mDry = dry; }

	void SetThreshold(double threshold) { mThreshold = threshold; }

	virtual void SetNote(CNote *note) override;

protected:
	CAudioEffect();

	// Controllable effects sends
	double	mDelay;
	double	mWet;
	double	mDry;
	double  mThreshold;

	int mWrloc;
	int mRdloc;

	double mTime = 5.0;

	std::vector<double> m_queueL;
	std::vector<double> m_queueR;

	const int MAXQUEUESIZE = 200000;
	const double M_PI = 3.14159265359;
	const double RANGE = .5;
	const int RATE = 2;
	const int LEVEL = 2;
};

