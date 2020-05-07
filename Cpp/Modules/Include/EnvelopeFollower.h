#pragma once
#include "SisoModule.h"

class EnvelopeFollower : public SisoModule
{
public:

	EnvelopeFollower(double ts);

	IInputPort* TimeInput() const;

	double Update(double x) override;

private:

	IInputPort* _pTimeInput;

	double _lastOutput;

	const double _ts;
};
