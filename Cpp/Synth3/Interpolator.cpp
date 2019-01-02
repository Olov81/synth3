#include "Interpolator.h"
#include "ISampleProvider.h"

Interpolator::Interpolator(ISampleProvider * pSampleProvider)
	:_pSampleProvider(pSampleProvider)
	,_position(0)
	,_lastSample(0)
	,_nextSample(pSampleProvider->GetNextSample())
{
	_pDecimiationInput = CreateInputPort();
	_pOutput = CreateOutputPort();
}

IInputPort * Interpolator::GetDecimationInput()
{
	return _pDecimiationInput;
}

IOutputPort * Interpolator::GetOutput()
{
	return _pOutput;
}

void Interpolator::Update()
{
	double output = GetNextSample(_pDecimiationInput->Read());

	_pOutput->Write(output);
}

double Interpolator::GetNextSample(double increment)
{
	double nextPosition = _position + increment;

	unsigned int numberOfNewSamples = (unsigned int)(nextPosition) - (unsigned int)_position;

	for (unsigned int i = 0; i < numberOfNewSamples; ++i)
	{
		_lastSample = _nextSample;
		_nextSample = _pSampleProvider->GetNextSample();
	}

	_position = nextPosition - (int)nextPosition;

	return _position * _nextSample + (1 - _position)*_lastSample;
}


