#include "PsgNoiseChannel.h"

PsgNoiseChannel::PsgNoiseChannel(double ts, int decimation)
	:_noiseGenerator(decimation)
	, _envelope(ts)
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