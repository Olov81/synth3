#pragma once
class IOutputPort;

class IInputPort
{
public:

	virtual void Connect(IOutputPort* outputPort) = 0;

	virtual double Read() const = 0;

	virtual const IOutputPort* GetConnection() const = 0;
};

