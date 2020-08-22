#include "Ym2612Channel.h"

Ym2612Channel::Ym2612Channel(double ts, Ym2612Algorithm algorithm)
	:_carrierOne(ts)
	,_carrierTwo(ts)
	,_modulatorOne(ts)
	,_modulatorTwo(ts)
	, _pitch(2)
	,_mixer(4)
{
	ConnectInputs(_carrierOne);
	ConnectInputs(_carrierTwo);
	ConnectInputs(_modulatorOne);
	ConnectInputs(_modulatorTwo);
	SetAlgorithm(algorithm);

	_gain.GetInput()->Connect(_mixer.Output());
}

IInputPort* Ym2612Channel::GateInput()
{
	return _gate.GetInput();
}

IInputPort* Ym2612Channel::PitchInput()
{
	return _pitch.GetInputPort(0);
}

IInputPort* Ym2612Channel::DetuneInput()
{
	return _pitch.GetInputPort(1);
}

IInputPort* Ym2612Channel::GainInput()
{
	return _gain.GetGainInput();
}

IInputPort* Ym2612Channel::ModulatorOneFeedbackInput()
{
	return _modulatorOne.FeedbackAmountInput();
}

IOutputPort* Ym2612Channel::Output()
{
	return _gain.GetOutput();
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
	op.PitchInput()->Connect(_pitch.Output());
}

void Ym2612Channel::ResetAlgorithmConnections()
{
	_mixer.GetInputPort(0)->Set(0);
	_mixer.GetInputPort(1)->Set(0);
	_mixer.GetInputPort(2)->Set(0);
	_mixer.GetInputPort(3)->Set(0);

	_carrierOne.ModulationInput()->Set(0);
	_carrierTwo.ModulationInput()->Set(0);
	_modulatorOne.ModulationInput()->Set(0);
	_modulatorTwo.ModulationInput()->Set(0);
}

void Ym2612Channel::SetAlgorithm(Ym2612Algorithm algorithm)
{
	ResetAlgorithmConnections();
	
	switch (algorithm)
	{
	case Ym2612Algorithm::AlgorithmZero:
		SetAlgorithmOne();
		break;
	case Ym2612Algorithm::AlgorithmFive:
		SetAlgorithmSix();
		break;
	default: SetAlgorithmOne();
	}
}

void Ym2612Channel::SetAlgorithmOne()
{
	_carrierOne.ModulationInput()->Connect(_modulatorOne.Output());
	_modulatorTwo.ModulationInput()->Connect(_carrierOne.Output());
	_carrierTwo.ModulationInput()->Connect(_modulatorTwo.Output());
	_mixer.GetInputPort(0)->Connect(_carrierTwo.Output());
}

void Ym2612Channel::SetAlgorithmSix()
{
	_carrierOne.ModulationInput()->Connect(_modulatorOne.Output());
	_modulatorTwo.ModulationInput()->Connect(_modulatorOne.Output());
	_carrierTwo.ModulationInput()->Connect(_modulatorOne.Output());
	
	_mixer.GetInputPort(0)->Connect(_carrierOne.Output());
	_mixer.GetInputPort(1)->Connect(_modulatorTwo.Output());
	_mixer.GetInputPort(2)->Connect(_carrierTwo.Output());
}
