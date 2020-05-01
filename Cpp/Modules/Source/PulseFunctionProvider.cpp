#include "PulseFunctionProvider.h"

PulseFunctionProvider::PulseFunctionProvider()
: _high(0, 1, 0)
, _low(0,0,0.5)
{
}

const LinearFunction& PulseFunctionProvider::GetFunction(const double& omega) const
{
	return omega < _low.omega ? _high : _low;
}

void PulseFunctionProvider::SetPulseWidth(const double& pulseWidth)
{
	_low.omega = pulseWidth;
}
