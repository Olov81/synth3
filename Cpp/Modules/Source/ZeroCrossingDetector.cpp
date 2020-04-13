#include "ZeroCrossingDetector.h"

ZeroCrossingDetector::ZeroCrossingDetector(
	std::function<void()> onPositiveSlopeCrossing,
	std::function<void()> onNegativeSlopeCrossing)
: _onPositiveSlopeCrossing(std::move(onPositiveSlopeCrossing))
, _onNegativeSlopeCrossing(std::move(onNegativeSlopeCrossing))
, _lastValue(0.0)
{
}

void ZeroCrossingDetector::Update(double value)
{
	if(_lastValue <= 0 && value > 0)
	{
		_onPositiveSlopeCrossing();
	}
	else if(_lastValue >= 0 && value < 0)
	{
		_onNegativeSlopeCrossing();
	}

	_lastValue = value;
}
