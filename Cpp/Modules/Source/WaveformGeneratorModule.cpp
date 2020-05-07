#include "WaveformGeneratorModule.h"

WaveformGeneratorModule::WaveformGeneratorModule(IWaveformGenerator* waveformGenerator)
: _pWaveformGenerator(waveformGenerator)
, _zeroCrossingDetector(
	std::bind(&WaveformGeneratorModule::ResetPhase, this, std::placeholders::_1),
	[]() {})
, _pPitchInput(CreateInputPort())
, _pPhaseResetInput(CreateInputPort())
{
}

void WaveformGeneratorModule::Update()
{
	_zeroCrossingDetector.Update(_pPhaseResetInput->Read());
	const auto frequency = _pitchToFrequencyConverter.Update(_pPitchInput->Read());
	const auto output = _pWaveformGenerator->Update(frequency);
	Write(output);
}

IInputPort* WaveformGeneratorModule::PitchInput() const
{
	return _pPitchInput;
}

IInputPort* WaveformGeneratorModule::PhaseResetInput() const
{
	return _pPhaseResetInput;
}

void WaveformGeneratorModule::ResetPhase(const double& relativeTimeInstant) const
{
	_pWaveformGenerator->ResetPhase(relativeTimeInstant);
}

SyncWaveformGenerator::SyncWaveformGenerator(ILinearFunctionProvider* functionProvider)
: _syncFunctionProvider(functionProvider)
, _generator(&_syncFunctionProvider)
, _pPitchInput(CreateInputPort())
, _pFrequencyMultiplierInput(CreateInputPort())
{
}

void SyncWaveformGenerator::Update()
{
	_syncFunctionProvider.SetFrequencyMultiplier(_pFrequencyMultiplierInput->Read());

	const auto pitch = _pitchToFrequencyConverter.Update(_pPitchInput->Read());
	
	const auto output = _generator.Update(pitch);

	Write(output);
}

IInputPort* SyncWaveformGenerator::PitchInput() const
{
	return _pPitchInput;
}

IInputPort* SyncWaveformGenerator::FrequencyMultiplierInput() const
{
	return _pFrequencyMultiplierInput;
}
