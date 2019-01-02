#include "FilterModule.h"
#include "IFilter.h"

FilterModule::FilterModule(IFilter * pFilter)
	:_pFilter(pFilter)
{
}

double FilterModule::Update(double x)
{
	return _pFilter->Update(x);
}
