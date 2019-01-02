#include "SampleBuffer.h"

SampleBuffer::SampleBuffer(const double * pBuffer, unsigned int bufferLength)
	:_pBuffer(pBuffer)
	,_bufferLength(bufferLength)
	,_currentPosition(0)
	,_loopStart(0)
	,_loopEnd(bufferLength - 1)
	,_getNextSample(&SampleBuffer::GetNextSampleLoopDisabled)
{
	_pOutput = CreateOutputPort();
}

IOutputPort * SampleBuffer::GetOutput()
{
	return _pOutput;
}

void SampleBuffer::Update()
{
	double sample = (this->*_getNextSample)();

	_pOutput->Write(sample);
}

void SampleBuffer::SetLoopEnabled(bool enabled)
{
	_getNextSample = enabled ? &SampleBuffer::GetNextSampleLoopEnabled : &SampleBuffer::GetNextSampleLoopDisabled;
}

void SampleBuffer::SetLoopInterval(unsigned int start, unsigned int end)
{
	_loopStart = start;
	_loopEnd = end;
}

double SampleBuffer::GetNextSampleLoopEnabled()
{
	if (_currentPosition > _loopEnd)
	{
		_currentPosition = _loopStart;
	}

	return _pBuffer[_currentPosition++];
}

double SampleBuffer::GetNextSampleLoopDisabled()
{
	if (_currentPosition >= _bufferLength)
	{
		return 0.0;
	}

	return _pBuffer[_currentPosition++];
}