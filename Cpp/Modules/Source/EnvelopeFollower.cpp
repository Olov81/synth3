#include "EnvelopeFollower.h"

EnvelopeFollower::EnvelopeFollower(double ts)
: _pTimeInput(CreateInputPort())
, _lastOutput(0)
, _ts(ts)
{
}

IInputPort* EnvelopeFollower::TimeInput() const
{
	return _pTimeInput;
}

double EnvelopeFollower::Update(double x)
{
	const auto T = _pTimeInput->Read();

	const auto k = (x - _lastOutput) / T;

	_lastOutput = _lastOutput + k * _ts;

	return _lastOutput;
}
