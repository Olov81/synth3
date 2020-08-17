#pragma once
#include "SisoModule.h"

class BitCrusher : public SisoModule
{
public:

	BitCrusher();

	IInputPort* ResolutionInput();

private:

	IInputPort* _pResolutionInput;

	double Update(double x) override;
};
