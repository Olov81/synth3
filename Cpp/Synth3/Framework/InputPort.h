#pragma once
#include "IInputPort.h"

class InputPort : public IInputPort
{
public:

	InputPort();

	virtual void Connect(IOutputPort * pOutputPort);

	virtual double Read() const;

	virtual IOutputPort* GetConnection() const;

private:

	IOutputPort* _pOutputPort;
};
