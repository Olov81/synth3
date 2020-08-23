#pragma once
#include "DrumMachine.h"
#include "Ym2612Channel.h"

class Megadrive
{
public:

	Megadrive(double ts, size_t numberOfFmChannels, size_t numberOfDrumChannels);

	Ym2612Channel& FmChannel(size_t n);

	DrumMachine& Dac();

	IInputPort* GainInput();
	
	IOutputPort* LeftOutput();
	
	IOutputPort* RightOutput();
	
private:

	std::vector<shared_ptr<Ym2612Channel>> _fmChannels;
	DrumMachine _dac;
	Sum _leftMixer;
	Sum _rightMixer;
	Gain _leftOutputGain;
	Gain _rightOutputGain;
	Repeater _gainInput;
};
