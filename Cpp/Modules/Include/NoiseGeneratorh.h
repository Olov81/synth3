#pragma once
#include "Framework/Module.h"

class NoiseGenerator : public Module
{
public:

	NoiseGenerator(int decimation = 0);

	IOutputPort* Output();
	
	void Update() override;

private:

	IOutputPort* _pOutput;
	int _decimation;
	int _cycleCount = 0;
};


