#pragma once
#include <map>
#include <memory>

#include "Framework/Module.h"
#include <vector>

class ArraySink : public Module
{
public:

	IInputPort* GetInput(const char* name);

	double GetSample(const char* inputName, unsigned int sampleIndex);

	void Update() override;

private:

	class Sink
	{
	public:

		Sink(const char* name, IInputPort* pInputPort);

		const char* _name;
		IInputPort* _pInputPort;
		std::vector<double> _samples;
	};
	
	std::map<const char*,std::shared_ptr<Sink>> _sinks;
};

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
