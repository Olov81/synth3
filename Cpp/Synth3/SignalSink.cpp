#include "SignalSink.h"
#include <fstream>

IInputPort* ArraySink::GetInput(const char* name)
{
	if (_sinks.find(name) == _sinks.end())
	{
		_sinks.insert(std::make_pair(name, std::make_shared<Sink>(name, CreateInputPort())));
	}

	return _sinks[name]->_pInputPort;
}

double ArraySink::GetSample(const char* inputName, unsigned sampleIndex)
{
	return _sinks[inputName]->_samples[sampleIndex];
}

void ArraySink::Update()
{
	for (auto sink : _sinks)
	{
		auto sample = sink.second->_pInputPort->Read();
		sink.second->_samples.push_back(sample);
	}
}

ArraySink::Sink::Sink(const char* name, IInputPort* pInputPort)
: _name(name)
, _pInputPort(pInputPort)
{
}

SignalSink::SignalSink()
{
	_pInput = CreateInputPort();
}

IInputPort * SignalSink::GetInput()
{
	return _pInput;
}

double SignalSink::GetSample(unsigned int index)
{
	return _samples[index];
}

void SignalSink::Update()
{
	_samples.push_back(_pInput->Read());
}

void SignalSink::WriteCsv(const char* filePath)
{
	std::ofstream file;
	file.open(filePath);
	
	for (auto sample : _samples)
	{
		file << sample << ",";
	}

	file.close();
}
