#pragma once

#include "Module.h"

class IFilter;

class FilterModule : public Module
{
public:

	FilterModule(IFilter* pFilter);

	IInputPort* GetInput();

	IOutputPort* GetOutput();

	virtual void Update() override;

private:

	IFilter* _pFilter;
	IInputPort* _pInput;
	IOutputPort* _pOutput;

};