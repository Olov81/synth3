#include "InputPort.h"
#include "IOutputPort.h"

InputPort::InputPort()
	: _pOutputPort(nullptr)
	, _defaultValue(0)
{

}

void InputPort::Connect(IOutputPort* pOutputPort)
{
	_pOutputPort = pOutputPort;
}

double InputPort::Read() const
{
	return _pOutputPort == nullptr ? _defaultValue : _pOutputPort->Read();
}

IOutputPort * InputPort::GetConnection() const
{
	return _pOutputPort;
}

void InputPort::Set(const double& value)
{
	_defaultValue = value;
	_pOutputPort = nullptr;
}
