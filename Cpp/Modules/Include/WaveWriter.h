#pragma once
#include "Framework/Module.h"
#include "SoundFileWrite.h"

class WaveWriter : public Module
{
public:

	WaveWriter(const char* fileName);

	void Update() override;

	void Close();

private:

	IInputPort* _pInput;
	SoundHeader _header;
	SoundFileWrite _soundFileWrite;
};