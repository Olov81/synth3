#pragma once
#include "Framework/IOutputPort.h"
#include "Framework/Module.h"

class Panning : Module
{
public:

	Panning();
	IInputPort* Input();

	IInputPort* PanInput();

	IOutputPort* LeftOutput();

	IOutputPort* RightOutput();

	void Update() override;

private:

	IInputPort* _pInput;
	IInputPort* _pPanInput;
	IOutputPort* _pLeftOutput;
	IOutputPort* _pRightOutput;
};
