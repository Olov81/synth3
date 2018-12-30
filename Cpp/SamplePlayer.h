#pragma once

class SamplePlayer
{
public:

	SamplePlayer();

	void SetSample(const double* sample);

	double Update(double resampleFactor, double gate);

private:

	const double* _sample;

	double _currentPosition;

	double _oldGate;
};
