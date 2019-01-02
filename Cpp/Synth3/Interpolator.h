#pragma once

class ISampleProvider
{
public:

	virtual double GetNextSample() = 0;
};

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
