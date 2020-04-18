#pragma once
#include "SisoModule.h"

class PitchToFrequencyConverter : public SisoModule
{
	double Update(double x) override;
};
