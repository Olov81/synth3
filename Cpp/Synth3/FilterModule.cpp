#include "FilterModule.h"
#include "IFilter.h"

FilterModule::FilterModule(IFilter * pFilter)
	:_pFilter(pFilter)
{
	_pInput = CreateInputPort();
	_pOutput = CreateOutputPort();
}

IInputPort * FilterModule::GetInput()
{
	return _pInput;
}

IOutputPort * FilterModule::GetOutput()
{
	return _pOutput;
}

void FilterModule::Update()
{
	double output = _pFilter->Update(_pInput->Read());

	_pOutput->Write(output);
}
