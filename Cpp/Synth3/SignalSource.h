#pragma once
#include <initializer_list>
#include "Framework/Module.h"

class SignalSource : public Module
{
public:

	SignalSource(std::initializer_list<double> samples);

	IOutputPort* GetOutput();

	virtual void Update();

private:

	IOutputPort* _pOutput;

	std::initializer_list<double>::const_iterator _samples;
};

