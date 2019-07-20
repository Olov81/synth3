#pragma once
#include "Framework/Module.h"
#include <complex>

class WaveformGenerator : public Module
{
public:

	WaveformGenerator();

	void Update() override;

private:	
	
	typedef std::complex<double> ComplexT;

	IOutputPort* _pOutput;
	IInputPort* _pFrequencyInput;
	double _t;
	std::complex<double> _w[6];
};
