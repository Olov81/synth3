#pragma once
#include "EnvelopeGenerator.h"
#include "Lfo.h"
#include "MulltiOscillator.h"
#include "NoiseGeneratorh.h"
#include "Repeater.h"
#include "Framework/Module.h"

class PsgNoiseChannel : public Module
{
public:

	PsgNoiseChannel(double ts);

	IInputPort* GateInput();

	IEnvelopeGeneratorControl& Envelope();

	IOutputPort* Output();
	
	void Update() override;

private:

	NoiseGenerator _noiseGenerator;
	EnvelopeGenerator _envelope;
	Gain _amplifier;
	Gain _velocity;
	Repeater _gate;
};

class PsgToneChannel : public Module
{
public:

	PsgToneChannel(double fs);

	IInputPort* PitchInput();
	IInputPort* GateInput();
	IInputPort* DetuneInput();
	IInputPort* VolumeInput();
	IEnvelopeGeneratorControl& Envelope();
	ILfoControl& Vibrato();

	IOutputPort* Output();
	
	void Update() override;
	
private:

	EnvelopeGenerator _envelope;
	Lfo _vibrato;
	MultiOscillator _oscillator;
	Gain _velocity;
	Gain _amplifier;
	Gain _volume;
	Gain _vibratoGain;
	Sum _pitch;
	Repeater _gate;
};

class Psg
{
public:

	Psg(double fs);
	
	PsgToneChannel& ChannelOne();
	PsgToneChannel& ChannelTwo();
	PsgToneChannel& ChannelThree();
	PsgNoiseChannel& ChannelFour();
	
	IOutputPort* Output();
	
private:

	PsgToneChannel _channelOne;
	PsgToneChannel _channelTwo;
	PsgToneChannel _channelThree;
	PsgNoiseChannel _channelFour;
	Sum _mixer;
	Gain _outputGain;
};
