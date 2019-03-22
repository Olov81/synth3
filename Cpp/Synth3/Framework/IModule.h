#pragma once
class IInputPort;

class IModule
{
public:
	virtual ~IModule() = default;

	virtual void Update() = 0;

	virtual unsigned int GetNumberOfInputs() const = 0;

	virtual const IInputPort* GetInputPort(unsigned int index) const = 0;
};
