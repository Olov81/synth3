#include "PulseGenerator.h"

PulseGenerator::PulseGenerator()
: _waveformGenerator(&_functionProvider)
, _pPitchInput(CreateInputPort())
, _pPulseWidthInput(CreateInputPort())
{
	_pPulseWidthInput->Set(0.5);
}

void PulseGenerator::Update()
{
	_functionProvider.SetPulseWidth(_pPulseWidthInput->Read());
	const auto frequency = _pitchToFrequencyConverter.Update(_pPitchInput->Read());
	Write(_waveformGenerator.Update(frequency));
}

IInputPort* PulseGenerator::PitchInput() const
{
	return _pPitchInput;
}

IInputPort* PulseGenerator::PhaseResetInput() const
{
	return nullptr;
	//return _generatorModule.PhaseResetInput();
}

IInputPort* PulseGenerator::PulseWidthInput() const
{
	return _pPulseWidthInput;
}
