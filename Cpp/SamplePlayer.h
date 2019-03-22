#pragma once
#include "Framework/Module.h"
#include "Interpolator.h"
#include "ISampleProvider.h"
#include "TwoPoleLowpassFilter.h"
#include "SampleBuffer.h"
#include "Port.h"
#include "Inverter.h"

class IFilter;

class SamplePlayer : public Module
{
public:

	SamplePlayer(const double* pSampleBuffer, size_t bufferSize, IFilter* pFilter);

	virtual void Update();

	IInputPort* GetDecimationInput() const;

	IOutputPort* GetOutput() const;

private:

	class SampleProvider : public ISampleProvider
	{
	public:

		SampleProvider(const double* pSampleBuffer, size_t bufferSize, IFilter* pFilter);

		virtual double GetNextSample();

		void SetFilterCutoff(const double& cutoff) const;

	private:

		SampleBuffer _sampleBuffer;
		IFilter* _pFilter;
	};

	IOutputPort* _pOutputPort;

	IInputPort* _pDecimationInput;

	SampleProvider _sampleProvider;

	Interpolator _interpolator;
};
