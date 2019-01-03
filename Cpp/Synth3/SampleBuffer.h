#pragma once
#include "Framework/Module.h"

class SampleBuffer : public Module
{
public:

	SampleBuffer(const double* pBuffer, unsigned int bufferLength);

	IOutputPort* GetOutput();

	virtual void Update();

	void SetLoopEnabled(bool enabled);

	void SetLoopInterval(unsigned int start, unsigned int end);

private:

	double GetNextSampleLoopEnabled();

	double GetNextSampleLoopDisabled();

	IOutputPort* _pOutput;

	typedef double (SampleBuffer::*DoGetNextSample)();

	DoGetNextSample _getNextSample;

	const double* _pBuffer;

	unsigned int _bufferLength;

	unsigned int _currentPosition;

	unsigned int _loopStart;

	unsigned int _loopEnd;

};
