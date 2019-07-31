#include "FlankDetector.h"

FlankDetector::FlankDetector(
	double threshold,
	std::function<void()> onPositiveFlankDetected,
	std::function<void()> onNegativeFlankDetected)
: _lastValue(0.0)
, _threshold(threshold)
, _onPositiveFlankDetected(std::move(onPositiveFlankDetected))
, _onNegativeFlankDetected(std::move(onNegativeFlankDetected))
{
}

void FlankDetector::Update(double value)
{
	if (value - _lastValue > _threshold)
	{
		_onPositiveFlankDetected();
	}
	else if (value - _lastValue < -_threshold)
	{
		_onNegativeFlankDetected();
	}

	_lastValue = value;
}
