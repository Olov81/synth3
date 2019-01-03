#pragma once
#include "IOutputPort.h"

class OutputPort : public IOutputPort
{
public:

	OutputPort(IModule* pOwnerModule);

	virtual void Write(double value);

	virtual double Read() const;

	IModule* GetOwnerModule() const;

private:

	IModule* _pOwnerModule;

	double _value;
};

