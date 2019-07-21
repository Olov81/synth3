#pragma once
#include "SisoModule.h"

class Gain : public SisoModule
{
public:

	Gain();

	IInputPort* GetGainInput() const;

private:

	double Update(double x) override;

	IInputPort* _pGainInput;
};