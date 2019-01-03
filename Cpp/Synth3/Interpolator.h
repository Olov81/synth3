#pragma once
#include "Framework/Module.h"

class ISampleProvider;

class Interpolator : public Module
{
public:

	Interpolator(ISampleProvider* sampleProvider);

	IInputPort* GetDecimationInput();

	IOutputPort* GetOutput();

	virtual void Update();

private:

	double GetNextSample(double increment);

	ISampleProvider* _pSampleProvider;

	IInputPort* _pDecimiationInput;

	IOutputPort* _pOutput;

	double _position;

	double _lastSample;

	double _nextSample;


};
