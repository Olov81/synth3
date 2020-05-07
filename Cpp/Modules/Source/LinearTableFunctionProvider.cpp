#include "LinearTableFunctionProvider.h"
#include <utility>

LinearTableFunctionProvider::LinearTableFunctionProvider(std::vector<LinearFunction> table)
	: _table(std::move(table))
{
}

LinearFunction LinearTableFunctionProvider::GetFunction(const double& omega) const
{
	const double omegaStart = static_cast<int>(omega);
	const double omegaEnd = omegaStart + 1;

	return { WaveformPoint(omegaStart, 0), WaveformPoint(omegaEnd, 1) };

	//const double numberOfLaps = static_cast<int>(omega);
	//const double wrappedOmega = omega - numberOfLaps;
	//const auto pulseWidth = 0.5;
	//
	//if(wrappedOmega < pulseWidth)
	//{
	//	return { numberOfLaps, 1, numberOfLaps + pulseWidth, 1 };
	//}

	//return { numberOfLaps + pulseWidth, 0, numberOfLaps + 1, 0 };
	
	//for (size_t index = 0; index < _table.size() - 1; ++index)
	//{
	//	if (_table[index].omega <= omega && omega < _table[index + 1].omega)
	//	{
	//		return _table[index];
	//	}
	//}
	//
	//return _table[0];
}

const std::vector<LinearFunction>& LinearTableFunctionProvider::GetFunctions() const
{
	return _table;
}
