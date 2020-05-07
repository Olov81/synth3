#pragma once
#include "ILinearFunctionProvider.h"

class SyncFunctionProvider : public ILinearFunctionProvider
{
public:

	SyncFunctionProvider(ILinearFunctionProvider* pFunctionProvider);

	LinearFunction GetFunction(const double& omega) const override;

	void SetFrequencyMultiplier(const double& multiplier);

private:

	ILinearFunctionProvider* _pFunctionProvider;
	double _multiplier;
};
