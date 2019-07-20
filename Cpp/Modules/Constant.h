#pragma once
#include "Framework/Module.h"

class Constant : public Module
{
public:

	Constant(double value);

	void Update() override;

private:

	IOutputPort* _pOutput;

	double _value{};
};
