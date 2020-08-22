#pragma once
#include "FmOperator.h"
#include "Panning.h"
#include "Repeater.h"
#include "Sum.h"

enum class Ym2612Algorithm
{
	AlgorithmZero,
	AlgorithmFour,
	AlgorithmFive
};



class Ym2612Channel
{
public:

	Ym2612Channel(double ts, Ym2612Algorithm algorithm);

	IInputPort* GateInput();
	
	IInputPort* PitchInput();

	IInputPort* DetuneInput();
	
	IInputPort* GainInput();

	IInputPort* PanInput();
	
	IInputPort* ModulatorOneFeedbackInput();
	
	IOutputPort* LeftOutput();
	
	IOutputPort* RightOutput();

	IFmOperatorControl& CarrierOne();
	IFmOperatorControl& CarrierTwo();
	IFmOperatorControl& ModulatorOne();
	IFmOperatorControl& ModulatorTwo();

	void SetAlgorithm(Ym2612Algorithm algorithm);
	
private:

	FmOperator _carrierOne;
	FmOperator _carrierTwo;
	FmOperator _modulatorOne;
	FmOperator _modulatorTwo;
	Repeater _gate;
	Sum _pitch;
	Sum _mixer;
	Panning _panning;
	Gain _gain;
	
	void ConnectInputs(FmOperator& op);
	void ResetAlgorithmConnections();
	void SetAlgorithmOne();
	void SetAlgorithmFour();
	void SetAlgorithmSix();
};

