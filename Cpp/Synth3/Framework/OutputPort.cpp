#include "OutputPort.h"

OutputPort::OutputPort(IModule * pOwnerModule)
	:_pOwnerModule(pOwnerModule)
	,_value(0)
{
}

void OutputPort::Write(double value)
{
	_value = value;
}

double OutputPort::Read() const
{
	return _value;
}

IModule * OutputPort::GetOwnerModule() const
{
	return _pOwnerModule;
}
