#include "SamplePlayer.h"

SamplePlayer::SamplePlayer(const double * pSampleBuffer, size_t bufferSize)
	: _decimationPort()
	, _inverter()
	, _sampleProvider(pSampleBuffer, bufferSize)
	, _interpolator(&_sampleProvider)
{
	_inverter.GetInput()->Connect(_decimationPort.GetOutput());
	_sampleProvider.GetFilterCutoffInput()->Connect(_inverter.GetOutput());
	_interpolator.GetDecimationInput()->Connect(_decimationPort.GetOutput());
}

void SamplePlayer::Update()
{
}

IInputPort * SamplePlayer::GetDecimationInput()
{
	return _decimationPort.GetInput();
}

IOutputPort * SamplePlayer::GetOutput()
{
	return _interpolator.GetOutput();
}

SamplePlayer::SampleProvider::SampleProvider(const double * pSampleBuffer, size_t bufferSize)
	: _sampleBuffer(pSampleBuffer, bufferSize)
	, _lowpassFilter()
{
	_lowpassFilter.SetQ(1.0);
	_pFilterCutoffInput = CreateInputPort();
}

double SamplePlayer::SampleProvider::GetNextSample()
{
	return _lowpassFilter.Update(_sampleBuffer.GetNextSample());
}

void SamplePlayer::SampleProvider::Update()
{
	_lowpassFilter.SetCutoff(_pFilterCutoffInput->Read());
}

IInputPort * SamplePlayer::SampleProvider::GetFilterCutoffInput()
{
	return _pFilterCutoffInput;
}
