#include "PulseFunctionProvider.h"

PulseFunctionProvider::PulseFunctionProvider()
: _high(0, 1, 0)
, _low(0,0,0.5)
, _functions({ _high, _low })
{
}

LinearFunction PulseFunctionProvider::GetFunction(const double& omega) const
{
	return omega < _low.omega ? _high : _low;
}

const std::vector<LinearFunction>& PulseFunctionProvider::GetFunctions() const
{
	return _functions;
}

void PulseFunctionProvider::SetPulseWidth(const double& pulseWidth)
{
	_low.omega = pulseWidth;
}
