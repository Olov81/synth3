#pragma once
#include "Framework/Module.h"
#include "SampleBuffer.h"

class SampleBufferModule : public Module
{
public:

	SampleBufferModule(const double* pBuffer, unsigned int bufferLength);

	IOutputPort* GetOutput();

	virtual void Update();

	void SetLoopEnabled(bool enabled);

	void SetLoopInterval(unsigned int start, unsigned int end);

private:

	IOutputPort* _pOutput;

	SampleBuffer _sampleBuffer;
};
