#include "WaveWriter.h"


SoundHeader& SetupHeader(SoundHeader& header, int rate)
{
	header.setHighStereo();
	header.setSrate(rate);
	return header;
}

WaveWriter::WaveWriter(const char* fileName, int rate)
	: _pLeftInput(CreateInputPort())
	,_pRightInput(CreateInputPort())
	,_soundFileWrite(fileName, SetupHeader(_header, rate))
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
