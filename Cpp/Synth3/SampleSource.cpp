#include "SampleSource.h"

SampleSource::SampleSource(const double * pSamples, size_t sampleCount)
	:_pSamples(pSamples)
	, _sampleCount(sampleCount)
	,_index(0)
{
	_pOutputPort = CreateOutputPort();
}

IOutputPort * SampleSource::GetOutput()
{
	return _pOutputPort;
}

void SampleSource::Update()
{
	_pOutputPort->Write(_pSamples[_index]);

	if (_index < _sampleCount - 1)
	{
		++_index;
	}
}
