#include "SampleBufferModule.h"

SampleBufferModule::SampleBufferModule(const double * pBuffer, unsigned int bufferLength)
	:_sampleBuffer(pBuffer, bufferLength)
{
	_pOutput = CreateOutputPort();
}

IOutputPort * SampleBufferModule::GetOutput()
{
	return _pOutput;
}

void SampleBufferModule::Update()
{
	_pOutput->Write(_sampleBuffer.GetNextSample());
}

void SampleBufferModule::SetLoopEnabled(bool enabled)
{
	_sampleBuffer.SetLoopEnabled(enabled);
}

void SampleBufferModule::SetLoopInterval(unsigned int start, unsigned int end)
{
	_sampleBuffer.SetLoopInterval(start, end);
}
