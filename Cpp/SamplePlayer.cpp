#include "SamplePlayer.h"

SamplePlayer::SamplePlayer()
	:_sample(0)
	,_currentPosition(0)
	,_oldGate(0)
{
}

void SamplePlayer::SetSample(const double * sample)
{
	_sample = sample;
	_currentPosition = 0.0;
}

double SamplePlayer::Update(double resampleFactor, double gate)
{
	if (gate - _oldGate > 0)
	{
		_currentPosition = 0.0;
	}

	_oldGate = gate;
	
	unsigned long k = (unsigned long)_currentPosition;

	double interpfactor = _currentPosition - k;

	double y = (1 - interpfactor)*_sample[k] + interpfactor * _sample[k + 1];

	_currentPosition += resampleFactor;

	return y;
}
