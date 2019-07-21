#pragma once
#include "Source.h"

class Lfo : public Source
{
public:

	Lfo(double fs);

	void Update() override;

	IInputPort* GetFrequencyInput() const;

	IInputPort* GetAmplitudeInput() const;

	IInputPort* GetOffsetInput() const;

private:

	IInputPort* _pFrequencyInput;
	IInputPort* _pAmplitudeInput;
	IInputPort* _pOffsetInput;
	const double _ts;
	double _f;
};
