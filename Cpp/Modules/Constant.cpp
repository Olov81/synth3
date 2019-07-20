#include "Constant.h"

Constant::Constant(double value)
	:_value(value)
{
	_pOutput = CreateOutputPort();
}

void Constant::Update()
{
	_pOutput->Write(_value);
}
