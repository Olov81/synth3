#include "Ym2612Channel.h"

Ym2612Channel::Ym2612Channel(double ts, Ym2612Algorithm algorithm)
	:_carrierOne(ts)
	,_carrierTwo(ts)
	,_modulatorOne(ts)
	,_modulatorTwo(ts)
	,_mixer(4)
{
	ConnectInputs(_carrierOne);
	ConnectInputs(_carrierTwo);
	ConnectInputs(_modulatorOne);
	ConnectInputs(_modulatorTwo);
	SetAlgorithm(algorithm);
}

IInputPort* Ym2612Channel::GateInput()
{
	return _gate.GetInput();
}

IInputPort* Ym2612Channel::PitchInput()
{
	return _pitch.GetInput();
}

IOutputPort* Ym2612Channel::Output()
{
	return _mixer.Output();
}

IFmOperatorControl& Ym2612Channel::CarrierOne()
{
	return _carrierOne;
}

IFmOperatorControl& Ym2612Channel::CarrierTwo()
{
	return _carrierTwo;
}

IFmOperatorControl& Ym2612Channel::ModulatorOne()
{
	return _modulatorOne;
}

IFmOperatorControl& Ym2612Channel::ModulatorTwo()
{
	return _modulatorTwo;
}

void Ym2612Channel::ConnectInputs(FmOperator& op)
{
	op.GateInput()->Connect(_gate.GetOutput());
	op.PitchInput()->Connect(_pitch.GetOutput());
}

void Ym2612Channel::SetAlgorithm(Ym2612Algorithm algorithm)
{
	switch (algorithm)
	{
	case Ym2612Algorithm::AlgorithmOne:
		SetAlgorithmOne();
		break;
	default: SetAlgorithmOne();
	}
}

void Ym2612Channel::SetAlgorithmOne()
{
	_modulatorOne.FeedbackAmountInput()->Set(0.0);

	_carrierOne.ModulationInput()->Connect(_modulatorOne.Output());
	_modulatorTwo.ModulationInput()->Connect(_carrierOne.Output());
	_carrierTwo.ModulationInput()->Connect(_modulatorTwo.Output());
	_mixer.GetInputPort(0)->Connect(_carrierTwo.Output());
}
