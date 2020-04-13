#include "MoogFilter.h"
#include <corecrt_math_defines.h>

MoogFilter::MoogFilter()
	: _stageOutputs()
{
	_pFrequencyInput = CreateInputPort();
	_pResonanceInput = CreateInputPort();

	_pFrequencyInput->Set(0.5);
	_pResonanceInput->Set(0.1);
}

IInputPort* MoogFilter::GetFrequencyInput() const
{
	return _pFrequencyInput;
}

IInputPort* MoogFilter::GetResonanceInput() const
{
	return _pResonanceInput;
}

double MoogFilter::Update(double x)
{
	static const auto VT = 1.5; // Temperature constant

	const auto g = 1 - exp(-2 * M_PI * _pFrequencyInput->Read() / 2);

	auto stageInput = x - 4 * _pResonanceInput->Read() * _stageOutputs[NUMBER_OF_STAGES - 1]; // Input signal and feedback from last stage

	for (auto& stageOutput : _stageOutputs)
	{
		stageOutput = stageOutput + 2 * VT * g * (tanh(stageInput / (2 * VT)) - tanh(stageOutput / (2 * VT)));

		stageInput = stageOutput;
	}

	return _stageOutputs[NUMBER_OF_STAGES - 1];
}
