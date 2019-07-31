#pragma once
#include <functional>

class FlankDetector
{
public:

	FlankDetector(
		double threshold,
		std::function<void()> onPositiveFlankDetected,
		std::function<void()> onNegativeFlankDetected);

	void Update(double value);

private:

	double _lastValue;
	double _threshold;
	std::function<void()> _onPositiveFlankDetected;
	std::function<void()> _onNegativeFlankDetected;
};
