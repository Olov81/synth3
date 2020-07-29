#pragma once
#include "EnvelopeGenerator.h"
#include "Lfo.h"
#include "MulltiOscillator.h"
#include "Repeater.h"
#include "Framework/Module.h"

class PsgToneChannel : public Module
{
public:

	PsgToneChannel(double fs);

	IInputPort* PitchInput();
	IInputPort* GateInput();
	IInputPort* DetuneInput();
	const IEnvelopeGeneratorControl& Envelope();
	ILfoControl& Vibrato();

	IOutputPort* Output();
	
	void Update() override;
	
private:

	EnvelopeGenerator _envelope;
	Lfo _vibrato;
	MultiOscillator _oscillator;
	Gain _velocity;
	Gain _amplifier;
	Gain _vibratoGain;
	Sum _pitch;
	Repeater _gate;
};

class Psg : public Module
{
	
};
