#pragma once
#include "EnvelopeGenerator.h"
#include "Gain.h"
#include "Framework/Module.h"
#include "PitchToFrequencyConverter.h"

class IFmOperatorControl
{
public:
	
	virtual ~IFmOperatorControl() = default;

	virtual IInputPort* RateInput() = 0;
	virtual IInputPort* GainInput() = 0;
	virtual IEnvelopeGeneratorControl& Envelope() = 0;
};

class FmOperator : public Module, public IFmOperatorControl
{
public:

	FmOperator(double ts);

	IInputPort* GateInput();

	IInputPort* PitchInput();

	IInputPort* ModulationInput();

	IInputPort* FeedbackAmountInput();

	IInputPort* RateInput() override;

	IInputPort* GainInput() override;
	
	IOutputPort* Output();	

	IEnvelopeGeneratorControl& Envelope() override;

	void Update() override;

private:

	class ToneGenerator : Module
	{
	public:

		ToneGenerator(double ts);

		IInputPort* FrequencyInput();

		IInputPort* ModulationInput();

		IInputPort* FeedbackAmountInput();
		
		IOutputPort* Output();

		void Update() override;

	private:

		double _ts;
		double _t = 0;
		double _output = 0;
		IInputPort* _pFrequencyInput;
		IInputPort* _pModulationInput;
		IOutputPort* _pOutput;
		IInputPort* _pFeedbackAmountInput;
	};

	ToneGenerator _toneGenerator;
	PitchToFrequencyConverter _pitchToFrequencyConverter;
	Gain _frequencyRate;
	EnvelopeGenerator _envelope;
	Gain _amplifier;
	Gain _outputGain;
};
