#include "SignalSink.h"
#include <fstream>

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
