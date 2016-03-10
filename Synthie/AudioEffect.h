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

	virtual void Process(double *frameIn, double *frameOut, double time) = 0;

	void SetDelay(double delay) { mDelay = delay; }

	void SetWet(double wet) { mWet = wet; }

	void SetDry(double dry) { mDry = dry; }

	virtual void SetNote(CNote *note) override;

protected:
	CAudioEffect();

	// Controllable effects sends
	double	mDelay;
	double	mWet;
	double	mDry;

	int mWrloc;
	int mRdloc;

	double mTime = 5.0;

	std::vector<short> mQueue;

private:
	const int MAXQUEUESIZE = 200000;
};

