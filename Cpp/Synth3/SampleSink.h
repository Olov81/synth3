#pragma once
#include "Framework/Module.h"

class SampleSink : public Module
{
public:

	SampleSink(double* buffer, size_t bufferSize);

	IInputPort* GetInputPort();

	virtual void Update();

private:

	double* _buffer;
	size_t _bufferSize;
	IInputPort* _pInputPort;
	size_t _index;
};