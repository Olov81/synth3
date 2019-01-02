#pragma once
#include "../Module.h"
#include <vector>

class SignalSink : public Module
{
public:

	SignalSink();

	IInputPort* GetInput();

	double GetSample(unsigned int index);

	virtual void Update();

private:

	IInputPort* _pInput;

	std::vector<double> _samples;
};
