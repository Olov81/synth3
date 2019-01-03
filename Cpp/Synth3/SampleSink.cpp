#include "SampleSink.h"

SampleSink::SampleSink(double * pBuffer, size_t bufferSize)
	:_pBuffer(pBuffer)
	, _bufferSize(bufferSize)
	, _index(0)
{
	_pInputPort = CreateInputPort();
}

IInputPort * SampleSink::GetInputPort()
{
	return _pInputPort;
}

void SampleSink::Update()
{
	if (_index == _bufferSize)
	{
		return;
	}

	_pBuffer[_index++] = _pInputPort->Read();
}
