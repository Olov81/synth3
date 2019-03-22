#pragma once

class ISampleProvider;

class Interpolator
{
public:

	Interpolator(ISampleProvider* sampleProvider);

	double GetNextSample(double increment);

private:

	ISampleProvider* _pSampleProvider;

	double _position;

	double _lastSample;

	double _nextSample;
};
