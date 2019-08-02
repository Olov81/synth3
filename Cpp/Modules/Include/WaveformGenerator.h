#pragma once
#include "Source.h"
#include <complex>
#include "Waveforms.h"

class WaveformGenerator : public Source
{
public:


	WaveformGenerator(std::vector<LinearFunction> waveform);

	void Update() override;

	IInputPort* GetFrequencyInput() const;

	IInputPort* GetTuneInput() const;

private:	
	
	typedef std::complex<double> ComplexT;

	IInputPort* _pFrequencyInput;
	IInputPort* _pTuneInput;
	double _t;
	std::complex<double> _w[6];
	std::vector<LinearFunction> _waveform;

	const LinearFunction& GetFunction(double t, double T);

	std::complex<double> ComputeIntegral(unsigned mode, double t0, double t, double T);
};
