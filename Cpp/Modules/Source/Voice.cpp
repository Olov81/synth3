#include "Voice.h"


Voice::Voice(IOutputPort* pPitchOutput, IOutputPort* pGateOutput)
	:_pPitchOutput(pPitchOutput)
	,_pGateOutput(pGateOutput)
{
}

IOutputPort* Voice::PitchOutput()
{
	return _pPitchOutput;
}

IOutputPort* Voice::GateOutput()
{
	return _pGateOutput;
}

void Voice::NoteOn(int key, int velocity)
{
	_pPitchOutput->Write(key - 69.0);
	_pGateOutput->Write(velocity / 127.0);
}

void Voice::NoteOff()
{
	_pGateOutput->Write(0.0);
}
