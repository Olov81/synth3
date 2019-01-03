#pragma once
#include "Framework/Module.h"
#include "Interpolator.h"
#include "ISampleProvider.h"
#include "TwoPoleLowpassFilter.h"
#include "SampleBuffer.h"
#include "Port.h"
#include "Inverter.h"

class SamplePlayer : public Module
{
public:

	SamplePlayer(const double* pSampleBuffer, size_t bufferSize);

	virtual void Update();

	IInputPort* GetDecimationInput();

	IOutputPort* GetOutput();

private:

	class SampleProvider : public ISampleProvider, public Module
	{
	public:

		SampleProvider(const double* pSampleBuffer, size_t bufferSize);

		virtual double GetNextSample();

		virtual void Update();

		IInputPort* GetFilterCutoffInput();

	private:

		SampleBuffer _sampleBuffer;
		TwoPoleLowpassFilter _lowpassFilter;
		IInputPort* _pFilterCutoffInput;
	};

	Port _decimationPort;

	Inverter _inverter;

	SampleProvider _sampleProvider;

	Interpolator _interpolator;
};
