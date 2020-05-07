#include "SisoModule.h"

SisoModule::SisoModule()
	: _bypass(false)
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
	if(_bypass)
	{
		_pOutput->Write(_pInput->Read());
	}

	double output = Update(_pInput->Read());

	_pOutput->Write(output);
}

void SisoModule::SetBypass(bool bypass)
{
	_bypass = bypass;
}
