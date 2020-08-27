#pragma once
#include "FlankDetector.h"
#include "Gain.h"
#include "SoundFileRead.h"
#include "Sum.h"
#include "Framework/Module.h"

class Channel : public Module
{
public:

	Channel();

	IInputPort* GateInput();

	IInputPort* GainInput();
	
	IOutputPort* Output();

	void Update() override;

	void LoadSample(const char* sampleFileName);
	
private:

	SoundFileRead _soundFileRead;

	IInputPort* _pGateInput;

	IInputPort* _pGainInput;
	
	IOutputPort* _pOutput;

	FlankDetector _flankDetector;
	
	void OnTrigger();
};

class DrumMachine
{
public:

	DrumMachine(size_t channels);
	
	IOutputPort* Output();

	IInputPort* GainInput();
	
	Channel& GetChannel(size_t channel);

private:

	std::vector<std::shared_ptr<Channel>> _channels;

	Sum _mixer;

	Gain _outputGain;
};
