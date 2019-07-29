#include "WaveWriter.h"
#include "WaveformGenerator.h"
#include "Framework/ModuleRunner.h"
#include "Lfo.h"
#include "Gain.h"
#include <chrono>
#include "Sequencer.h"
#include "SignalSink.h"

template<class F>
double MeasureRunTimeInSeconds(const F& f)
{
	const auto begin = std::chrono::steady_clock::now();
	f();
	const auto end = std::chrono::steady_clock::now();

	const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	return microseconds * 1e-6;
}

int main()
{
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 5;

	WaveWriter waveWriter("Apa.wav");
	
	WaveformGenerator generator;
	
	Gain gain;
	gain.GetGainInput()->Set(0.5);

	Sequencer sequencer(ts, 100, {
		SequencerEvent("C4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("C4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("C4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("E4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("F4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("E4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("E4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.0 / 16, 1.0),
		SequencerEvent("C4", 1.0 / 4, 1.0 / 8, 1.0),
		});

	Lfo lfo(fs);
	lfo.GetFrequencyInput()->Set(0.4);
	lfo.GetAmplitudeInput()->Set(800);
	lfo.GetOffsetInput()->Set(1220);

	SignalSink sequencerFrequencies;
	SignalSink generatorOutput;

	sequencerFrequencies.GetInput()->Connect(sequencer.GetFrequencyOutput());
	generator.GetFrequencyInput()->Connect(sequencer.GetFrequencyOutput());
	generatorOutput.GetInput()->Connect(generator.GetOutput());
	gain.GetInput()->Connect(generator.GetOutput());
	waveWriter.GetInput()->Connect(gain.GetOutput());

	ModuleRunner runner(&waveWriter);

	auto update = [&]() {runner.Run(static_cast<int>(duration * fs)); };

	auto runTime = MeasureRunTimeInSeconds(update);

	waveWriter.Close();

	std::cout << "Performance: " << duration/runTime << " x faster than real time" << std::endl;
}
