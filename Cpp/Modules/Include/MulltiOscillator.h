#pragma once
#include "WaveformGenerator.h"
#include "Sum.h"
#include "SignalSplitter.h"
#include "PitchToFrequencyConverter.h"
#include "Gain.h"
#include "WaveformGeneratorModule.h"
#include "LinearTableFunctionProvider.h"

class MultiOscillator : public Module
{
public:

	MultiOscillator(
		size_t numberOfVoices,
		std::vector<LinearFunction> waveform,
		double voiceInterval);

	IInputPort* PitchInput() const;

	IInputPort* DetuneInput();

	IOutputPort* Output() const;

	void Update() override;

private:

	class Voice : public Module
	{
	public:

		Voice(std::vector<LinearFunction> waveform, double detuneMultiplicator, double transpose);

		IInputPort* PitchInput();

		IInputPort* DetuneInput();

		IOutputPort* Output() const;

		void Update() override;

	private:

		LinearTableFunctionProvider _functionProvider;
		WaveformGenerator _generator;
		WaveformGeneratorModule _generatorModule;
		Sum _pitchMixer;
		PitchToFrequencyConverter _pitchToFrequencyConverter;
		Gain _detuneGain;
	};

	Gain _detuneRepeater;

	std::vector<std::shared_ptr<Voice>> _voices;

	SignalSplitter _pitchSplitter;

	Sum _mixer;
};
