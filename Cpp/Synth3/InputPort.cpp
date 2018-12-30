#include "InputPort.h"
#include "IOutputPort.h"

InputPort::InputPort()
	: _pOutputPort(0)
{

}

void InputPort::Connect(IOutputPort* pOutputPort)
{
	_pOutputPort = pOutputPort;
}

double InputPort::Read() const
{
	return _pOutputPort == 0 ? 0 : _pOutputPort->Read();
}

IOutputPort * InputPort::GetConnection() const
{
	return _pOutputPort;
}
