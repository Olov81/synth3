#include "Decimator.h"

Decimator::Decimator(int decimation)
	: _decimation(decimation)
{
}

double Decimator::Update(double x)
{
	if(_counter == 0)
	{
		_output = x;
	}

	_counter = (_counter + 1) % _decimation;
	
	return _output;
}
