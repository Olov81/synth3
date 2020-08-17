#include "BitCrusher.h"

BitCrusher::BitCrusher()
{
	_pResolutionInput = CreateInputPort();
}

IInputPort* BitCrusher::ResolutionInput()
{
	return _pResolutionInput;
}

double BitCrusher::Update(double x)
{
	const auto res = _pResolutionInput->Read();

	return static_cast<int>(res * x) / res;
}
