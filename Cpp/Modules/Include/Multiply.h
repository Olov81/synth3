#pragma once
#include "Framework/Module.h"

class Multiply : public Module
{
public:

	Multiply(size_t numberOfInputs);

	void Update() override;

	IOutputPort* Output() const;

private:

	IOutputPort* _pOutput;
};
