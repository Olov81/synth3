#include "SignalSink.h"

SignalSink::SignalSink()
{
	_pInput = CreateInputPort();
}

IInputPort * SignalSink::GetInput()
{
	return _pInput;
}

double SignalSink::GetSample(unsigned int index)
{
	return _samples[index];
}

void SignalSink::Update()
{
	_samples.push_back(_pInput->Read());
}
