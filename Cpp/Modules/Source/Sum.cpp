#include "Sum.h"

Sum::Sum(size_t numberOfInputs)
{
	for(size_t n = 0; n < numberOfInputs; ++n)
	{
		CreateInputPort();
	}

	_pOutput = CreateOutputPort();
}

void Sum::Update()
{
	double y = 0.0;

	for (size_t n = 0; n < GetNumberOfInputs(); ++n)
	{
		y += GetInputPort(n)->Read();
	}

	_pOutput->Write(y);
}
	
IOutputPort* Sum::Output() const
{
	return _pOutput;
}
