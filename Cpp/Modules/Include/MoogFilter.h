#pragma once
#include "SisoModule.h"

class MoogFilter : public SisoModule
{
public:

	MoogFilter();

	IInputPort* GetFrequencyInput() const;

	IInputPort* GetResonanceInput() const;

private:

	static const int NUMBER_OF_STAGES = 4;

	IInputPort* _pFrequencyInput;
	IInputPort* _pResonanceInput;
	double _stageOutputs[NUMBER_OF_STAGES] = { 0.0, 0.0, 0.0, 0.0 };

	double Update(double x) override;
};
