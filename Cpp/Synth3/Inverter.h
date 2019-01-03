#pragma once
#include "SisoModule.h"

class Inverter : public SisoModule
{
private:

	virtual double Update(double x);
};