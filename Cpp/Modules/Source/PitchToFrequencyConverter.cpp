#pragma once

#include "PitchToFrequencyConverter.h"
#include "Globals.h"
#include <complex>

double PitchToFrequencyConverter::Update(double x)
{
	return ZERO_PITCH_FREQUENCY*std::pow(2.0, x / 12.0);
}