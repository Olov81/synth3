#include "DrumMachine.h"

Channel::Channel()
	 : _flankDetector(1e-3, [this] {OnTrigger(); }, [] {})
{
	_pGateInput = CreateInputPort();
	_pGainInput = CreateInputPort();
	_pOutput = CreateOutputPort();

	_pGainInput->Set(1.0);
}

IInputPort* Channel::GateInput()
{
	return _pGateInput;
}

IInputPort* Channel::GainInput()
{
	return _pGainInput;
}

IOutputPort* Channel::Output()
{
	return _pOutput;
}

void Channel::Update()
{
	_flankDetector.Update(_pGateInput->Read());

	const auto gain = _pGainInput->Read();
	
	_pOutput->Write(gain * _soundFileRead.getNextSampleDouble());
}

void Channel::LoadSample(const char* sampleFileName)
{
	_soundFileRead.setFile(sampleFileName);
}

void Channel::OnTrigger()
{
	_soundFileRead.reset();
}

DrumMachine::DrumMachine(size_t channels)
	: _mixer(channels)
{
	for(size_t n = 0; n < channels; ++n)
	{
		_channels.push_back(std::make_shared<Channel>());
		_mixer.GetInputPort(n)->Connect(_channels.back()->Output());
	}
}

IOutputPort* DrumMachine::Output()
{
	return _mixer.Output();
}

Channel& DrumMachine::GetChannel(size_t channel)
{
	return *_channels[channel];
}


