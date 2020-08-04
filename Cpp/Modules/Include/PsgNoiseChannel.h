#pragma once
#include "EnvelopeGenerator.h"
#include "Gain.h"
#include "NoiseGeneratorh.h"
#include "Repeater.h"

class PsgNoiseChannel : public Module
{
public:

	PsgNoiseChannel(double ts, int decimation);

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

