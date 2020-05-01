#include "WaveformGeneratorModule.h"

WaveformGeneratorModule::WaveformGeneratorModule(IWaveformGenerator* waveformGenerator)
: _pWaveformGenerator(waveformGenerator)
, _zeroCrossingDetector(
	std::bind(&WaveformGeneratorModule::ResetPhase, this, std::placeholders::_1),
	[]() {})
, _pFrequencyInput(CreateInputPort())
, _pPhaseResetInput(CreateInputPort())
{
}

void WaveformGeneratorModule::Update()
{
	_zeroCrossingDetector.Update(_pPhaseResetInput->Read());
	const auto output = _pWaveformGenerator->Update(_pFrequencyInput->Read());
	Write(output);
}

IInputPort* WaveformGeneratorModule::FrequencyInput() const
{
	return _pFrequencyInput;
}

IInputPort* WaveformGeneratorModule::PhaseResetInput() const
{
	return _pPhaseResetInput;
}

void WaveformGeneratorModule::ResetPhase(const double& relativeTimeInstant) const
{
	_pWaveformGenerator->ResetPhase(relativeTimeInstant);
}
