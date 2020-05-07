#include "SyncFunctionProvider.h"

SyncFunctionProvider::SyncFunctionProvider(ILinearFunctionProvider* pFunctionProvider)
: _pFunctionProvider(pFunctionProvider)
, _multiplier(1.0)
{

}

LinearFunction SyncFunctionProvider::GetFunction(const double& omega) const
{
	const auto completeCycles = static_cast<int>(_multiplier * omega);

	const auto newOmega = _multiplier * omega - completeCycles;

	const auto f = _pFunctionProvider->GetFunction(newOmega);

	const auto functionOmega = (completeCycles + f.omega) / _multiplier;

	return {f.k*_multiplier, f.start, functionOmega};
}

void SyncFunctionProvider::SetFrequencyMultiplier(const double& multiplier)
{
	_multiplier = multiplier;
}
