#pragma once
#include "Source.h"
#include <complex>
#include "Waveforms.h"
#include "ZeroCrossingDetector.h"

class WaveformGenerator : public Source
{
public:


	WaveformGenerator(std::vector<LinearFunction> waveform);

	void Update() override;

	IInputPort* GetFrequencyInput() const;

	IInputPort* GetTuneInput() const;

	IInputPort* GetPhaseResetInput() const;

	typedef double ComplexT;

private:	
	

	IInputPort* _pFrequencyInput;
	IInputPort* _pTuneInput;
	IInputPort* _pPhaseResetInput;
	double _t;
	std::complex<double> _w[6];
	std::vector<LinearFunction> _waveform;
	ZeroCrossingDetector _zeroCrossingDetector;

	const LinearFunction& GetFunction(double t, double T);

	std::complex<double> ComputeIntegral(unsigned mode, double t0, double t, double T);

	void ResetPhase(const double& relativeTimeInstant);
};
