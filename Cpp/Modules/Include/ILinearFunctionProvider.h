#pragma once
#include "Waveforms.h"

class ILinearFunctionProvider
{
public:

	virtual ~ILinearFunctionProvider() = default;

	virtual const LinearFunction& GetFunction(const double& omega) const = 0;
};

