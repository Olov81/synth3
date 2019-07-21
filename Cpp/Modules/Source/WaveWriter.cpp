#include "WaveWriter.h"


WaveWriter::WaveWriter(const char* fileName)
	: _soundFileWrite(fileName, _header)
{
	_pInput = CreateInputPort();
}

void WaveWriter::Update()
{
	_soundFileWrite.writeSampleDouble(_pInput->Read());
}

void WaveWriter::Close()
{
	_soundFileWrite.close();
}

IInputPort* WaveWriter::GetInput() const
{
	return _pInput;
}
