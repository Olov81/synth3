#include "NoiseGeneratorh.h"

NoiseGenerator::NoiseGenerator(int decimation)
	: _decimation(decimation)
{
	_pOutput = CreateOutputPort();
}

IOutputPort* NoiseGenerator::Output()
{
	return _pOutput;
}

void NoiseGenerator::Update()
{
	if(_cycleCount == _decimation)
	{
		const auto value = 2.0 * (rand() / static_cast <double> (RAND_MAX)) - 1.0;
		_pOutput->Write(value);
		_cycleCount = 0;
	}
	else
	{
		++_cycleCount;
	}
}
