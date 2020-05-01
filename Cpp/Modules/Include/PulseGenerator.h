#pragma once
#include "WaveformGenerator.h"
#include "PulseFunctionProvider.h"
#include "PitchToFrequencyConverter.h"
#include "Source.h"

class PulseGenerator : public Source
{
public:

	PulseGenerator();

	void Update() override;

	IInputPort* PitchInput() const;

	IInputPort* PhaseResetInput() const;

	IInputPort* PulseWidthInput() const;

private:

	PulseFunctionProvider _functionProvider;
	WaveformGenerator _waveformGenerator;
	PitchToFrequencyConverter _pitchToFrequencyConverter;
	IInputPort* _pPitchInput;
	IInputPort* _pPulseWidthInput;
};
