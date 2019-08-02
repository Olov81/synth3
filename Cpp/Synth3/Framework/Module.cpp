#include "Module.h"
#include <algorithm>

Module::Module()
{
}

IInputPort* Module::CreateInputPort()
{
	InputPort* pPort = new InputPort();

	_inputPorts.push_back(pPort);

	return pPort;
}

IOutputPort* Module::CreateOutputPort()
{
	OutputPort* pPort = new OutputPort(this);

	_outputPorts.push_back(pPort);

	return pPort;
}

unsigned int Module::GetNumberOfInputs() const
{
	return _inputPorts.size();
}

const IInputPort* Module::GetInputPort(unsigned int index) const
{
	return _inputPorts[index];
}

IInputPort* Module::GetInputPort(unsigned int index)
{
	return _inputPorts[index];
}