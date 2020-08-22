#include "Megadrive.h"

Megadrive::Megadrive(double ts, size_t numberOfDrumChannels)
	:_dac(numberOfDrumChannels)
	,_mixer(7)
{
	for(auto n = 0; n < 6; ++n)
	{
		auto fmChannel = make_shared<Ym2612Channel>(ts, Ym2612Algorithm::AlgorithmZero);
		_mixer.GetInputPort(n)->Connect(fmChannel->Output());
		_fmChannels.push_back(fmChannel);
	}
	_mixer.GetInputPort(6)->Connect(_dac.Output());
	_outputGain.GetInput()->Connect(_mixer.Output());
	_outputGain.GetGainInput()->Set(0.5);
}

Ym2612Channel& Megadrive::FmChannel(size_t n)
{
	return *_fmChannels[n];
}

DrumMachine& Megadrive::Dac()
{
	return _dac;
}

IInputPort* Megadrive::GainInput()
{
	return _outputGain.GetGainInput();
}

IOutputPort* Megadrive::Output()
{
	return _outputGain.GetOutput();
}
