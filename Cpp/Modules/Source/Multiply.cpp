#include "Multiply.h"

Multiply::Multiply(size_t numberOfInputs)
{
	for (size_t n = 0; n < numberOfInputs; ++n)
	{
		CreateInputPort();
	}

	_pOutput = CreateOutputPort();
}

void Multiply::Update()
{
	auto y = 0.0;

	for (size_t n = 0; n < GetNumberOfInputs(); ++n)
	{
		y *= GetInputPort(n)->Read();
	}

	_pOutput->Write(y);
}

IOutputPort* Multiply::Output() const
{
	return _pOutput;
}
