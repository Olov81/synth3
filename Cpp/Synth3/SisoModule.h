#pragma once
#include "Framework/Module.h"

class SisoModule : public Module
{
public:

	SisoModule();

	IInputPort* GetInput();

	IOutputPort* GetOutput();

	virtual void Update();

	void SetBypass(bool bypass);

private:

	virtual double Update(double x) = 0;

	IInputPort* _pInput;
	IOutputPort* _pOutput;
	bool _bypass;
};