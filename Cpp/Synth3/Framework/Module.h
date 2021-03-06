#pragma once
#include "IModule.h"
#include "InputPort.h"
#include "OutputPort.h"
#include <vector>

class Module : public IModule
{
public:

	unsigned int GetNumberOfInputs() const;

	const IInputPort * GetInputPort(unsigned int index) const;

	IInputPort* GetInputPort(unsigned index);

protected:

	Module();

	IInputPort* CreateInputPort();

	IOutputPort* CreateOutputPort();

private:

	std::vector<InputPort*> _inputPorts;
	
	std::vector<OutputPort*> _outputPorts;
};