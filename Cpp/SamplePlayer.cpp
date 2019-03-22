#include "SamplePlayer.h"

SamplePlayer::SamplePlayer(const double * pSampleBuffer, size_t bufferSize, IFilter* pFilter)
	: _sampleProvider(pSampleBuffer, bufferSize, pFilter)
	, _interpolator(&_sampleProvider)
{
	_pOutputPort = CreateOutputPort();
	_pDecimationInput = CreateInputPort();
}

void SamplePlayer::Update()
{
	const double decimation = _pDecimationInput->Read();

	_sampleProvider.SetFilterCutoff(1.0/decimation);

	_pOutputPort->Write(_interpolator.GetNextSample(decimation));
}

IInputPort * SamplePlayer::GetDecimationInput() const
{
	return _pDecimationInput;
}

IOutputPort * SamplePlayer::GetOutput() const
{
	return _pOutputPort;
}

SamplePlayer::SampleProvider::SampleProvider(const double * pSampleBuffer, size_t bufferSize, IFilter* pFilter)
	: _sampleBuffer(pSampleBuffer, bufferSize)
	, _pFilter(pFilter)
{
}

double SamplePlayer::SampleProvider::GetNextSample()
{
	return _pFilter->Update(_sampleBuffer.GetNextSample());
}

void SamplePlayer::SampleProvider::SetFilterCutoff(const double& cutoff) const
{
	_pFilter->SetCutoffFrequency(cutoff);
}
