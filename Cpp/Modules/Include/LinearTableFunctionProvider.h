#pragma once
#include "ILinearFunctionProvider.h"

class LinearTableFunctionProvider : public ILinearFunctionProvider
{
public:

	LinearTableFunctionProvider(std::vector<LinearFunction> table);

	LinearFunction GetFunction(const double& omega) const override;

private:

	std::vector<LinearFunction> _table;
};
