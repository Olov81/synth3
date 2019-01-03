#pragma once
#include "Framework/Module.h"

class SampleSource : public Module
{
public:

	SampleSource(const double* pSamples, size_t sampleCount);

	IOutputPort* GetOutput();

	virtual void Update();

private:

	const double* _pSamples;
	size_t _sampleCount;
	IOutputPort* _pOutputPort;
	size_t _index;
};
