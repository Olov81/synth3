#pragma once
#include "Source.h"
#include "FlankDetector.h"

class IEnvelopeGeneratorControl
{
public:
	
	virtual ~IEnvelopeGeneratorControl() = default;

	virtual IInputPort* AttackInput() const = 0;
	virtual IInputPort* DecayInput() const = 0;
	virtual IInputPort* SustainInput() const = 0;
	virtual IInputPort* ReleaseInput() const = 0;
};

class EnvelopeGenerator : public Source, public IEnvelopeGeneratorControl
{
public:

	EnvelopeGenerator(double ts, double velocitySensitivity = 0.0);

	void Update() override;

	IInputPort* GateInput() const;

	IInputPort* AttackInput() const override;

	IInputPort* DecayInput() const override;

	IInputPort* SustainInput() const override;

	IInputPort* ReleaseInput() const override;

private:

	FlankDetector _flankDetector;
	IInputPort* _pGateInput;
	IInputPort* _pAttackInput;
	IInputPort* _pDecayInput;
	IInputPort* _pSustainInput;
	IInputPort* _pReleaseInput;
	double _ts;
	double _velocitySensitivity;
	double _velocity = 0.0;
	double _output;
	typedef double(EnvelopeGenerator::* Phase)();
	Phase _currentPhase;
	
	double AttackPhase();
	double DecayPhase();
	double SustainPhase();
	double ReleasePhase();
	double SilencePhase();
	void BeginAttackPhase();
	void BeginReleasePhase();
};
