#include "Megadrive.h"

Megadrive::Megadrive(double ts, size_t numberOfFmChannels, size_t numberOfDrumChannels)
	:_dac(numberOfDrumChannels)
	,_psg(1/ts)
	,_leftMixer(numberOfFmChannels + 2)
	,_rightMixer(numberOfFmChannels + 2)
{
	for(size_t n = 0; n < numberOfFmChannels; ++n)
	{
		auto fmChannel = make_shared<Ym2612Channel>(ts, Ym2612Algorithm::AlgorithmZero);
		_leftMixer.GetInputPort(n)->Connect(fmChannel->LeftOutput());
		_rightMixer.GetInputPort(n)->Connect(fmChannel->RightOutput());
		_fmChannels.push_back(fmChannel);
	}
	
	_leftMixer.GetInputPort(numberOfFmChannels)->Connect(_dac.Output());
	_rightMixer.GetInputPort(numberOfFmChannels)->Connect(_dac.Output());
	
	_leftMixer.GetInputPort(numberOfFmChannels + 1)->Connect(_psg.Output());
	_rightMixer.GetInputPort(numberOfFmChannels + 1)->Connect(_psg.Output());
	
	_leftOutputGain.GetInput()->Connect(_leftMixer.Output());
	_leftOutputGain.GetGainInput()->Connect(_gainInput.GetOutput());

	_rightOutputGain.GetInput()->Connect(_rightMixer.Output());
	_rightOutputGain.GetGainInput()->Connect(_gainInput.GetOutput());

	_gainInput.GetInput()->Set(0.5);
}

Ym2612Channel& Megadrive::FmChannel(size_t n)
{
	return *_fmChannels[n];
}

DrumMachine& Megadrive::Dac()
{
	return _dac;
}

MasterSystemPsg& Megadrive::Psg()
{
	return _psg;
}

IInputPort* Megadrive::GainInput()
{
	return _gainInput.GetInput();
}

IOutputPort* Megadrive::LeftOutput()
{
	return _leftOutputGain.GetOutput();
}

IOutputPort* Megadrive::RightOutput()
{
	return _rightOutputGain.GetOutput();
}