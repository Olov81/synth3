#pragma once
#include "WaveformGenerator.h"
#include "Sum.h"
#include "SignalSplitter.h"
#include "PitchToFrequencyConverter.h"

class MultiOscillator : public Module
{
public:

	MultiOscillator(size_t numberOfVoices, std::vector<LinearFunction> waveform);

	IInputPort* PitchInput() const;

	IOutputPort* Output() const;

	void Update() override;

private:

	class Voice : public Module
	{
	public:

		Voice();

		IInputPort* PitchInput();

		IInputPort* DetuneInput();

		IOutputPort* Output() const;

		void Update() override;

	private:

		WaveformGenerator _generator;
		Sum _pitchMixer;
		PitchToFrequencyConverter _pitchToFrequencyConverter;
	};

	std::vector<std::shared_ptr<Voice>> _voices;

	SignalSplitter _pitchSplitter;

	Sum _mixer;
};
