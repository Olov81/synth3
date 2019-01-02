#include "SignalSource.h"

SignalSource::SignalSource(std::initializer_list<double> samples)
	:_samples(samples.begin())
{
	_pOutput = CreateOutputPort();
}

IOutputPort * SignalSource::GetOutput()
{
	return _pOutput;
}

void SignalSource::Update()
{
	double sample = *_samples;

	_pOutput->Write(sample);

	++_samples;
}
