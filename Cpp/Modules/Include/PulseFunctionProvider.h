#pragma once
#include "ILinearFunctionProvider.h"

class PulseFunctionProvider : public ILinearFunctionProvider
{
public:

	explicit PulseFunctionProvider();

	const LinearFunction& GetFunction(const double& omega) const override;

	void SetPulseWidth(const double& pulseWidth);

private:

	LinearFunction _high;
	LinearFunction _low;
};
