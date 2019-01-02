#include "SisoModule.h"

SisoModule::SisoModule()
{
	_pInput = CreateInputPort();
	_pOutput = CreateOutputPort();
}

IInputPort * SisoModule::GetInput()
{
	return _pInput;
}

IOutputPort * SisoModule::GetOutput()
{
	return _pOutput;
}

void SisoModule::Update()
{
	double output = Update(_pInput->Read());

	_pOutput->Write(output);
}
