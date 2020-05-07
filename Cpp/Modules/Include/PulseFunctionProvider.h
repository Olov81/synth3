#pragma once
#include "ILinearFunctionProvider.h"

class PulseFunctionProvider : public ILinearFunctionProvider
{
public:

	explicit PulseFunctionProvider();

	LinearFunction GetFunction(const double& omega) const override;

	const std::vector<LinearFunction>& GetFunctions() const override;
	
	void SetPulseWidth(const double& pulseWidth);

private:

	LinearFunction _high;
	LinearFunction _low;
	std::vector<LinearFunction> _functions;
};
