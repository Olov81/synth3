#pragma once
#include "Framework/IOutputPort.h"
#include "Framework/Module.h"

class Voice
{
public:

	Voice(IOutputPort* pPitchOutput, IOutputPort* pGateOutput);

	IOutputPort* PitchOutput();
	IOutputPort* GateOutput();

	void NoteOn(int key, int velocity);

	void NoteOff();
	
private: 

	IOutputPort* _pPitchOutput;
	IOutputPort* _pGateOutput;
};
