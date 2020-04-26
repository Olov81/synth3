#pragma once
#include "Source.h"
#include "FlankDetector.h"

class Lfo : public Source
{
public:

	Lfo(double fs);

	void Update() override;

	IInputPort* FrequencyInput() const;

	IInputPort* AmplitudeInput() const;

	IInputPort* OffsetInput() const;

	IInputPort* DelayInput() const;

	IInputPort* GateInput() const;

private:

	IInputPort* _pFrequencyInput;
	IInputPort* _pAmplitudeInput;
	IInputPort* _pOffsetInput;
	IInputPort* _pDelayInput;
	IInputPort* _pGateInput;

	const double _ts;
	double _f;
	double _timeSinceReset;
	FlankDetector _flankDetector;

	void ResetTimer();
};
