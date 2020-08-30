#pragma once
#include "Framework/Module.h"
#include "SoundFileWrite.h"

class WaveWriter : public Module
{
public:

	WaveWriter(const char* fileName, int rate = 44100);

	void Update() override;

	void Close();

	IInputPort* LeftInput() const;
	IInputPort* RightInput() const;

private:

	IInputPort* _pLeftInput;
	IInputPort* _pRightInput;
	SoundHeader _header;
	SoundFileWrite _soundFileWrite;
};