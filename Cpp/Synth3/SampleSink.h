#pragma once
#include "Framework/Module.h"

class SampleSink : public Module
{
public:

	SampleSink(double* pBuffer, size_t bufferSize);

	IInputPort* GetInputPort();

	virtual void Update();

private:

	double* _pBuffer;
	size_t _bufferSize;
	IInputPort* _pInputPort;
	size_t _index;
};