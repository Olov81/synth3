#include "SyncFunctionProvider.h"

SyncFunctionProvider::SyncFunctionProvider(ILinearFunctionProvider* pFunctionProvider)
: _pFunctionProvider(pFunctionProvider)
, _multiplier(1.0)
{

}

LinearFunction SyncFunctionProvider::GetFunction(const double& omega) const
{	
	const auto f = _pFunctionProvider->GetFunction(_multiplier * omega);

	return {f.k * _multiplier, f.m, f.omegaStart / _multiplier, f.omega / _multiplier };
	//const auto completeCycles = static_cast<int>(_multiplier * omega);

	//const auto newOmega = _multiplier * omega - completeCycles;

	//const auto f = _pFunctionProvider->GetFunction(newOmega);

	//const auto functionOmegaStart = (completeCycles + f.omegaStart) / _multiplier;
	//const auto functionOmegaEnd = (completeCycles + f.omega) / _multiplier;

	//return {f.k*_multiplier, f.start, functionOmegaStart, functionOmegaEnd};
}

const std::vector<LinearFunction>& SyncFunctionProvider::GetFunctions() const
{
	return _pFunctionProvider->GetFunctions();
}

void SyncFunctionProvider::SetFrequencyMultiplier(const double& multiplier)
{
	_multiplier = multiplier;
}
