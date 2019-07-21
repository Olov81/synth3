#include "Constant.h"

Constant::Constant(double value)
	:_value(value)
{
}

void Constant::Update()
{
	Write(_value);
}
