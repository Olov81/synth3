#pragma once

#include "SisoModule.h"

class IFilter;

class FilterModule : public SisoModule
{
public:

	FilterModule(IFilter* pFilter);

private:

	IFilter* _pFilter;

	virtual double Update(double x);
};