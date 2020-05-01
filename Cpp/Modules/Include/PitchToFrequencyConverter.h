#pragma once
#include "SisoModule.h"

class PitchToFrequencyConverter : public SisoModule
{
public:

	double Update(double x) override;
};
