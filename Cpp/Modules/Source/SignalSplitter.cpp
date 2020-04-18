#include "SignalSplitter.h"

SignalSplitter::SignalSplitter(size_t numberOfOutputs)
	:_pInput(CreateInputPort())
{
	for(size_t n = 0; n < numberOfOutputs; ++n)
	{
		_outputs.push_back(CreateOutputPort());
	}
}

void SignalSplitter::Update()
{
	const auto input = _pInput->Read();

	for (auto output : _outputs)
	{
		output->Write(input);
	}
}

IInputPort* SignalSplitter::Input() const
{
	return _pInput;
}

IOutputPort* SignalSplitter::GetOutput(size_t n) const
{
	return _outputs[n];
}
