#pragma once
#include "FmOperator.h"
#include "Repeater.h"
#include "Sum.h"

enum class Ym2612Algorithm
{
	AlgorithmOne
};

class Ym2612Channel
{
public:

	Ym2612Channel(double ts, Ym2612Algorithm algorithm);

	IInputPort* GateInput();
	
	IInputPort* PitchInput();

	IInputPort* GainInput();
	
	IOutputPort* Output();

	IFmOperatorControl& CarrierOne();
	IFmOperatorControl& CarrierTwo();
	IFmOperatorControl& ModulatorOne();
	IFmOperatorControl& ModulatorTwo();
	
private:

	FmOperator _carrierOne;
	FmOperator _carrierTwo;
	FmOperator _modulatorOne;
	FmOperator _modulatorTwo;
	Repeater _gate;
	Repeater _pitch;
	Sum _mixer;
	Gain _gain;
	
	void ConnectInputs(FmOperator& op);
	void SetAlgorithm(Ym2612Algorithm algorithm);
	void SetAlgorithmOne();
};

