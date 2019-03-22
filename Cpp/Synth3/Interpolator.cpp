#include "Interpolator.h"
#include "ISampleProvider.h"

Interpolator::Interpolator(ISampleProvider * pSampleProvider)
	:_pSampleProvider(pSampleProvider)
	,_position(0)
	,_lastSample(0)
	,_nextSample(pSampleProvider->GetNextSample())
{
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


