#pragma once
#include "ZeroCrossingDetector.h"
#include "IWaveformGenerator.h"
#include "Source.h"

class WaveformGeneratorModule : public Source
{
public:

	WaveformGeneratorModule(IWaveformGenerator* waveformGenerator);

	void Update() override;

	IInputPort* FrequencyInput() const;

	IInputPort* PhaseResetInput() const;

private:

	IWaveformGenerator* _pWaveformGenerator;
	ZeroCrossingDetector _zeroCrossingDetector;
	IInputPort* _pFrequencyInput;
	IInputPort* _pPhaseResetInput;

	void ResetPhase(const double& relativeTimeInstant) const;
};
