#pragma once
#include "Framework/Module.h"

class Sum : public Module
{
public:

	Sum(size_t numberOfInputs);

	void Update() override;

	IOutputPort* GetOutput() const;

private:

	IOutputPort* _pOutput;
};