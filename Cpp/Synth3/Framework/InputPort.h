#pragma once
#include "IInputPort.h"

class InputPort : public IInputPort
{
public:

	InputPort();

	void Connect(IOutputPort * pOutputPort) override;

	double Read() const override;

	IOutputPort* GetConnection() const override;

	void Set(const double& value) override;

private:

	IOutputPort* _pOutputPort;

	double _defaultValue;
};
