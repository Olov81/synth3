#pragma once
#include <complex>
#include "Waveforms.h"
#include "IWaveformGenerator.h"
#include "ILinearFunctionProvider.h"

class WaveformGenerator : public IWaveformGenerator
{
public:

	WaveformGenerator(ILinearFunctionProvider* functionProvider);

	double Update(const double& frequency) override;

	void ResetPhase(const double& relativeTimeInstant) override;

	typedef double ComplexT;

private:	
	
	double _t;
	std::complex<double> _w[6];
	ILinearFunctionProvider* _pFunctionProvider;

	LinearFunction GetFunction(double t, double T) const;

	std::complex<double> ComputeIntegral(unsigned mode, double t0, double t, double T);
};
