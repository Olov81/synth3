#pragma once
#include "Framework/IOutputPort.h"
#include "Framework/Module.h"

class Voice : public Module
{
public:

	Voice();

	IOutputPort* PitchOutput();
	IOutputPort* GateOutput();

	void NoteOn(int key, int velocity);

	void NoteOff();

	void Update() override;
	
private: 

	IOutputPort* _pPitchOutput;
	IOutputPort* _pGateOutput;
};
