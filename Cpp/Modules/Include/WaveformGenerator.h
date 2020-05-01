#pragma once
#include "Source.h"
#include <complex>
#include "Waveforms.h"
#include "ZeroCrossingDetector.h"
#include "IWaveformGenerator.h"

class WaveformGenerator : public IWaveformGenerator
{
public:

	WaveformGenerator(std::vector<LinearFunction> waveform);

	double Update(const double& frequency) override;

	void ResetPhase(const double& relativeTimeInstant) override;

	typedef double ComplexT;

private:	
	
	double _t;
	std::complex<double> _w[6];
	std::vector<LinearFunction> _waveform;

	const LinearFunction& GetFunction(double t, double T);

	std::complex<double> ComputeIntegral(unsigned mode, double t0, double t, double T);
};
