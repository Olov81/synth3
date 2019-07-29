#pragma once
#include "Framework/Module.h"
#include <vector>

class SignalSink : public Module
{
public:

	SignalSink();

	IInputPort* GetInput();

	double GetSample(unsigned int index);

	virtual void Update();

	void WriteCsv(const char* filePath);

private:

	IInputPort* _pInput;

	std::vector<double> _samples;
};
