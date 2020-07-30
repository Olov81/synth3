#include "Psg.h"

PsgNoiseChannel::PsgNoiseChannel(double ts)
	:_noiseGenerator(8)
	,_envelope(ts)
{
	_envelope.GateInput()->Connect(_gate.GetOutput());
	
	_amplifier.GetInput()->Connect(_noiseGenerator.Output());
	_amplifier.GetGainInput()->Connect(_envelope.Output());
	
	_velocity.GetInput()->Connect(_amplifier.GetOutput());
	_velocity.GetGainInput()->Connect(_gate.GetOutput());
}

IInputPort* PsgNoiseChannel::GateInput()
{
	return _gate.GetInput();
}

IEnvelopeGeneratorControl& PsgNoiseChannel::Envelope()
{
	return _envelope;
}

IOutputPort* PsgNoiseChannel::Output()
{
	return _velocity.GetOutput();
}

void PsgNoiseChannel::Update()
{
	
}

PsgToneChannel::PsgToneChannel(double fs)
	:_envelope(1.0 / fs)
	, _vibrato(fs)
	, _oscillator(1, Waveforms::Square(), 0)
	, _pitch(2)
{
	_vibratoGain.GetInput()->Connect(_vibrato.Output());
	_vibratoGain.GetGainInput()->Set(0.5);
	
	_pitch.GetInputPort(1)->Connect(_vibratoGain.GetOutput());
	
	_oscillator.PitchInput()->Connect(_pitch.Output());

	_envelope.GateInput()->Connect(_gate.GetOutput());
	
	_amplifier.GetInput()->Connect(_oscillator.Output());
	_amplifier.GetGainInput()->Connect(_envelope.Output());

	_velocity.GetInput()->Connect(_amplifier.GetOutput());
	_velocity.GetGainInput()->Connect(_gate.GetOutput());

	_volume.GetInput()->Connect(_velocity.GetOutput());
	_volume.GetGainInput()->Set(1.0);
}

IInputPort* PsgToneChannel::PitchInput()
{
	return _pitch.GetInputPort(0);
}

IInputPort* PsgToneChannel::GateInput()
{
	return _gate.GetInput();
}

IInputPort* PsgToneChannel::DetuneInput()
{
	return _pitch.GetInputPort(1);
}

IInputPort* PsgToneChannel::VolumeInput()
{
	return _volume.GetGainInput();
}

IEnvelopeGeneratorControl& PsgToneChannel::Envelope()
{
	return _envelope;
}

ILfoControl& PsgToneChannel::Vibrato()
{
	return _vibrato;
}

IOutputPort* PsgToneChannel::Output()
{
	return _volume.GetOutput();
}

void PsgToneChannel::Update()
{
	
}

Psg::Psg(double fs)
	: _channelOne(fs)
	,_channelTwo(fs)
	,_channelThree(fs)
	,_channelFour(1/fs)
	,_mixer(4)
{
	_mixer.GetInputPort(0)->Connect(_channelOne.Output());
	_mixer.GetInputPort(1)->Connect(_channelTwo.Output());
	_mixer.GetInputPort(2)->Connect(_channelThree.Output());
	_mixer.GetInputPort(3)->Connect(_channelFour.Output());
	
	_outputGain.GetGainInput()->Set(0.35);
	_outputGain.GetInput()->Connect(_mixer.Output());
}

PsgToneChannel& Psg::ChannelOne()
{
	return _channelOne;
}

PsgToneChannel& Psg::ChannelTwo()
{
	return _channelTwo;
}

PsgToneChannel& Psg::ChannelThree()
{
	return _channelThree;
}

PsgNoiseChannel& Psg::ChannelFour()
{
	return _channelFour;
}

IOutputPort* Psg::Output()
{
	return _outputGain.GetOutput();
}
