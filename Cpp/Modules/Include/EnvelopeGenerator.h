#pragma once
#include "Source.h"
#include "FlankDetector.h"

class EnvelopeGenerator : public Source
{
public:

	EnvelopeGenerator(double ts);

	void Update() override;

	IInputPort* GateInput() const;

	IInputPort* AttackInput() const;

	IInputPort* DecayInput() const;

	IInputPort* SustainInput() const;

	IInputPort* ReleaseInput() const;

private:

	FlankDetector _flankDetector;
	IInputPort* _pGateInput;
	IInputPort* _pAttackInput;
	IInputPort* _pDecayInput;
	IInputPort* _pSustainInput;
	IInputPort* _pReleaseInput;
	double _ts;
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
