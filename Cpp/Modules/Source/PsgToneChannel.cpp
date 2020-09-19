#include "PsgToneChannel.h"

PsgToneChannel::PsgToneChannel(double fs, std::vector<LinearFunction> waveform, int decimation)
	:_envelope(1.0 / fs)
	, _vibrato(fs)
	, _oscillator(1, waveform, 0)
	, _pitch(2)
	, _decimator(decimation)
{
	_vibratoGain.GetInput()->Connect(_vibrato.Output());
	_vibratoGain.GetGainInput()->Set(0.5);

	_pitch.GetInputPort(1)->Connect(_vibratoGain.GetOutput());

	_oscillator.PitchInput()->Connect(_pitch.Output());

	_envelope.GateInput()->Connect(_gate.GetOutput());

	_amplifier.GetInput()->Connect(_oscillator.Output());
	_amplifier.GetGainInput()->Connect(_envelope.Output());

	_volume.GetInput()->Connect(_amplifier.GetOutput());
	_volume.GetGainInput()->Set(1.0);

	_decimator.GetInput()->Connect(_volume.GetOutput());
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
	return _decimator.GetOutput();
}

void PsgToneChannel::Update()
{

}
