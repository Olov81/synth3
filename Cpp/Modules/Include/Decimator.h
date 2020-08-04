#pragma once
#include "SisoModule.h"

class Decimator : public SisoModule
{
public:

	Decimator(int decimation);

private:

	double Update(double x) override;
	
	int _decimation;
	int _counter = 0;
	double _output = 0;
};
