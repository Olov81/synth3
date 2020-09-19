#include "EnvelopeGenerator.h"

EnvelopeGenerator::EnvelopeGenerator(double ts, double velocitySensitivity)
	: _flankDetector(
		1e-3,
		[this] { BeginAttackPhase(); },
		[this] { BeginReleasePhase(); })
	, _ts(ts)
	, _output(0)
	, _currentPhase(&EnvelopeGenerator::SilencePhase)
{
	_pGateInput = CreateInputPort();
	_pAttackInput = CreateInputPort();
	_pDecayInput = CreateInputPort();
	_pSustainInput = CreateInputPort();
	_pReleaseInput = CreateInputPort();
	_pGainInput = CreateInputPort();
	_pVelocitySensitivityInput = CreateInputPort();
	
	_pAttackInput->Set(1e-2);
	_pDecayInput->Set(0.5);
	_pSustainInput->Set(0.0);
	_pReleaseInput->Set(0.1);
	_pGainInput->Set(1.0);
	_pVelocitySensitivityInput->Set(velocitySensitivity);
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

IInputPort* EnvelopeGenerator::GainInput() const
{
	return _pGainInput;
}

IInputPort* EnvelopeGenerator::VelocitySensitivity() const
{
	return _pVelocitySensitivityInput;
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
	_velocity = _pGateInput->Read();
	_currentPhase = &EnvelopeGenerator::AttackPhase;
}

void EnvelopeGenerator::BeginReleasePhase()
{
	_currentPhase = &EnvelopeGenerator::ReleasePhase;
}

void EnvelopeGenerator::Update()
{
	const auto gate = _pGateInput->Read() > 1e-3 ? 1.0 : 0.0;
	const auto gain = _pGainInput->Read();
	const auto velocitySensitivity = _pVelocitySensitivityInput->Read();
	
	_flankDetector.Update(gate);
	const auto velocity = velocitySensitivity * _velocity + (1 - velocitySensitivity);
	const auto output = gain * velocity * (this->*_currentPhase)();
	Write(output);
}
