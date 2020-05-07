#include "LinearTableFunctionProvider.h"
#include <utility>

LinearTableFunctionProvider::LinearTableFunctionProvider(std::vector<LinearFunction> table)
	: _table(std::move(table))
{
}

LinearFunction LinearTableFunctionProvider::GetFunction(const double& omega) const
{
	for (size_t index = 0; index < _table.size() - 1; ++index)
	{
		if (_table[index].omega <= omega && omega < _table[index + 1].omega)
		{
			return _table[index];
		}
	}
	
	return _table[0];
}
