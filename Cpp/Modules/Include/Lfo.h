#pragma once
#include "Source.h"
#include "FlankDetector.h"

class ILfoControl
{
public:
	virtual ~ILfoControl() = default;

	virtual IInputPort* FrequencyInput() const = 0;
	virtual IInputPort* AmplitudeInput() const = 0;
	virtual IInputPort* OffsetInput() const = 0;
	virtual IInputPort* DelayInput() const = 0;
};

class Lfo : public Source, public ILfoControl
{
public:

	Lfo(double fs);

	void Update() override;

	IInputPort* FrequencyInput() const override;

	IInputPort* AmplitudeInput() const override;

	IInputPort* OffsetInput() const override;

	IInputPort* DelayInput() const override;

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
