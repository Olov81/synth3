#include "Gain.h"

Gain::Gain()
{
	_pGainInput = CreateInputPort();
}

IInputPort* Gain::GetGainInput() const
{
	return _pGainInput;
}

double Gain::Update(const double x)
{
	return x * _pGainInput->Read();
}
