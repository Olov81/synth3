#pragma once
#include "Waveforms.h"

class ILinearFunctionProvider
{
public:

	virtual ~ILinearFunctionProvider() = default;

	virtual LinearFunction GetFunction(const double& omega) const = 0;
};

