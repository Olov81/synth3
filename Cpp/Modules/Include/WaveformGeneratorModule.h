#pragma once
#include "ZeroCrossingDetector.h"
#include "IWaveformGenerator.h"
#include "Source.h"
#include "PitchToFrequencyConverter.h"
#include "ILinearFunctionProvider.h"
#include "SyncFunctionProvider.h"
#include "WaveformGenerator.h"

class WaveformGeneratorModule : public Source
{
public:

	WaveformGeneratorModule(IWaveformGenerator* waveformGenerator);

	void Update() override;

	IInputPort* PitchInput() const;

	IInputPort* PhaseResetInput() const;

private:

	IWaveformGenerator* _pWaveformGenerator;
	ZeroCrossingDetector _zeroCrossingDetector;
	IInputPort* _pPitchInput;
	IInputPort* _pPhaseResetInput;
	PitchToFrequencyConverter _pitchToFrequencyConverter;

	void ResetPhase(const double& relativeTimeInstant) const;
};

class SyncWaveformGenerator : public Source
{
public:

	explicit SyncWaveformGenerator(ILinearFunctionProvider* pFunctionProvider);

	void Update() override;

	IInputPort* PitchInput() const;

	IInputPort* FrequencyMultiplierInput() const;
	
private:

	SyncFunctionProvider _syncFunctionProvider;
	WaveformGenerator _generator;
	PitchToFrequencyConverter _pitchToFrequencyConverter;
	IInputPort* _pPitchInput;
	IInputPort* _pFrequencyMultiplierInput;
};