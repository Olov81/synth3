#pragma once
#include <functional>

class ZeroCrossingDetector
{
public:

	ZeroCrossingDetector(
		std::function<void(const double&)> onPositiveSlopeCrossing,
		std::function<void()> onNegativeSlopeCrossing);

	void Update(double value);

private:

	std::function<void(const double&)> _onPositiveSlopeCrossing;
	std::function<void()> _onNegativeSlopeCrossing;
	double _lastValue;
};
