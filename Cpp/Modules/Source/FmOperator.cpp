#include "FmOperator.h"
#include <cmath>
#include <corecrt_math_defines.h>

FmOperator::FmOperator(double ts)
: _toneGenerator(ts)
, _envelope(ts, 1.0)
{
	_frequencyRate.GetGainInput()->Set(1.0);
	_frequencyRate.GetInput()->Connect(_pitchToFrequencyConverter.GetOutput());
	_toneGenerator.FrequencyInput()->Connect(_frequencyRate.GetOutput());

	_amplifier.GetInput()->Connect(_toneGenerator.Output());
	_amplifier.GetGainInput()->Connect(_envelope.Output());

	_outputGain.GetInput()->Connect(_amplifier.GetOutput());
}

IInputPort* FmOperator::GateInput()
{
	return _envelope.GateInput();
}

IInputPort* FmOperator::PitchInput()
{
	return _pitchToFrequencyConverter.GetInput();
}

IInputPort* FmOperator::ModulationInput()
{
	return _toneGenerator.ModulationInput();
}

IInputPort* FmOperator::FeedbackAmountInput()
{
	return _toneGenerator.FeedbackAmountInput();
}

IInputPort* FmOperator::RateInput()
{
	return _frequencyRate.GetGainInput();
}

IInputPort* FmOperator::GainInput()
{
	return _outputGain.GetGainInput();
}

IOutputPort* FmOperator::Output()
{
	return _outputGain.GetOutput();
}

IEnvelopeGeneratorControl& FmOperator::Envelope()
{
	return _envelope;
}

void FmOperator::Update()
{
}

FmOperator::ToneGenerator::ToneGenerator(double ts)
	:_ts(ts)
{
	_pFrequencyInput = CreateInputPort();
	_pModulationInput = CreateInputPort();
	_pFeedbackAmountInput = CreateInputPort();
	_pOutput = CreateOutputPort();

}

IInputPort* FmOperator::ToneGenerator::FrequencyInput()
{
	return _pFrequencyInput;
}

IInputPort* FmOperator::ToneGenerator::ModulationInput()
{
	return _pModulationInput;
}

IInputPort* FmOperator::ToneGenerator::FeedbackAmountInput()
{
	return _pFeedbackAmountInput;
}

IOutputPort* FmOperator::ToneGenerator::Output()
{
	return _pOutput;
}

void FmOperator::ToneGenerator::Update()
{
	_f += _pFrequencyInput->Read();
	const auto modulation = _pModulationInput->Read();
	const auto fb = _pFeedbackAmountInput->Read();
	
	_output = sin(2 * M_PI * _f * _ts + 5*modulation + fb * _output);

	_pOutput->Write(_output);

	_t += _ts;
}
