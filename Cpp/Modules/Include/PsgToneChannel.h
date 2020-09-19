#pragma once
#include "Decimator.h"
#include "EnvelopeGenerator.h"
#include "Gain.h"
#include "Lfo.h"
#include "MulltiOscillator.h"
#include "Repeater.h"
#include "Sum.h"

class PsgToneChannel : public Module
{
public:

	PsgToneChannel(double fs, std::vector<LinearFunction> waveform, int decimation = 1);

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
	Gain _amplifier;
	Gain _volume;
	Gain _vibratoGain;
	Sum _pitch;
	Repeater _gate;
	Decimator _decimator;
};

