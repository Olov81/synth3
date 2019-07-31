#include "EnvelopeGenerator.h"

EnvelopeGenerator::EnvelopeGenerator(double ts)
	: _flankDetector(
		1e-3,
		std::bind(&EnvelopeGenerator::BeginAttackPhase, this),
		std::bind(&EnvelopeGenerator::BeginReleasePhase, this))
	, _ts(ts)
	, _output(0)
	, _currentPhase(&EnvelopeGenerator::SilencePhase)
{
	_pGateInput = CreateInputPort();
	_pAttackInput = CreateInputPort();
	_pDecayInput = CreateInputPort();
	_pSustainInput = CreateInputPort();
	_pReleaseInput = CreateInputPort();

	_pAttackInput->Set(1e-2);
	_pDecayInput->Set(0.5);
	_pSustainInput->Set(0.0);
	_pReleaseInput->Set(0.1);
}

IInputPort* EnvelopeGenerator::GateInput() const
{
	return _pGateInput;
}

IInputPort* EnvelopeGenerator::AttackInput() const
{
	return _pAttackInput;
}

IInputPort* EnvelopeGenerator::DecayInput() const
{
	return _pDecayInput;
}

IInputPort* EnvelopeGenerator::SustainInput() const
{
	return _pSustainInput;
}

IInputPort* EnvelopeGenerator::ReleaseInput() const
{
	return _pReleaseInput;
}

double EnvelopeGenerator::AttackPhase()
{
	const auto attackTime = _pAttackInput->Read();

	_output += _ts / attackTime;

	if(_output >= 1.0)
	{
		_output = 1.0;
		_currentPhase = &EnvelopeGenerator::DecayPhase;
	}

	return _output;
}

double EnvelopeGenerator::DecayPhase()
{
	const auto decayTime = _pDecayInput->Read();
	const auto sustainLevel = _pSustainInput->Read();

	_output -= _ts / decayTime;

	if (_output <= sustainLevel)
	{
		_output = sustainLevel;
		_currentPhase = &EnvelopeGenerator::SustainPhase;
	}

	return _output;
}

double EnvelopeGenerator::SustainPhase()
{
	return _pSustainInput->Read();
}

double EnvelopeGenerator::ReleasePhase()
{
	const auto releaseTime = _pReleaseInput->Read();

	_output -= _ts / releaseTime;

	if(_output <= 0.0)
	{
		_output = 0.0;
		_currentPhase = &EnvelopeGenerator::SilencePhase;
	}

	return _output;
}

double EnvelopeGenerator::SilencePhase()
{
	return 0.0;
}

void EnvelopeGenerator::BeginAttackPhase()
{
	_currentPhase = &EnvelopeGenerator::AttackPhase;
}

void EnvelopeGenerator::BeginReleasePhase()
{
	_currentPhase = &EnvelopeGenerator::ReleasePhase;
}

void EnvelopeGenerator::Update()
{
	auto gate = _pGateInput->Read();
	_flankDetector.Update(gate);
	auto output = (this->*_currentPhase)();
	Write(output);
}
