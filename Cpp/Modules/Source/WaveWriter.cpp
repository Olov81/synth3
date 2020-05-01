#include "WaveWriter.h"


SoundHeader& SetupHeader(SoundHeader& header)
{
	header.setHighStereo();
	return header;
}

WaveWriter::WaveWriter(const char* fileName)
	: _pLeftInput(CreateInputPort())
	,_pRightInput(CreateInputPort())
	,_soundFileWrite(fileName, SetupHeader(_header))
{
}

void WaveWriter::Update()
{
	_soundFileWrite.writeSampleDouble(_pLeftInput->Read());
	_soundFileWrite.writeSampleDouble(_pRightInput->Read());
}

void WaveWriter::Close()
{
	_soundFileWrite.close();
}

IInputPort* WaveWriter::LeftInput() const
{
	return _pLeftInput;
}

IInputPort* WaveWriter::RightInput() const
{
	return _pRightInput;
}
