#pragma once
#include "Source.h"
#include <complex>

class WaveformGenerator : public Source
{
public:

	WaveformGenerator();

	void Update() override;

	IInputPort* GetFrequencyInput() const;

private:	
	
	typedef std::complex<double> ComplexT;

	IInputPort* _pFrequencyInput;
	double _t;
	std::complex<double> _w[6];
};
