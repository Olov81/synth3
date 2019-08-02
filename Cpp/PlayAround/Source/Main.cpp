#include "WaveWriter.h"
#include "WaveformGenerator.h"
#include "Framework/ModuleRunner.h"
#include "Lfo.h"
#include "Gain.h"
#include <chrono>
#include "Sequencer.h"
#include "SignalSink.h"
#include "EnvelopeGenerator.h"
#include "Sum.h"

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
	
	WaveformGenerator generatorOne(Waveforms::Sawtooth());
	WaveformGenerator generatorTwo(Waveforms::Sawtooth());
	generatorTwo.GetTuneInput()->Set(11.95);
	
	Gain outputLevel;
	outputLevel.GetGainInput()->Set(0.2);

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
		SequencerEvent("C4", 1.0 / 4, 3.0 / 16, 1.0),
		},-24);

	Gain vca;
	Sum mixer(2);
	EnvelopeGenerator envelope(ts);
	envelope.SustainInput()->Set(1.0);
	envelope.ReleaseInput()->Set(5e-2);
	SignalSink logger;

	generatorOne.GetFrequencyInput()->Connect(sequencer.GetFrequencyOutput());
	generatorTwo.GetFrequencyInput()->Connect(sequencer.GetFrequencyOutput());
	mixer.GetInputPort(0)->Connect(generatorOne.GetOutput());
	//mixer.GetInputPort(1)->Connect(generatorTwo.GetOutput());
	envelope.GateInput()->Connect(sequencer.GetGateOutput());
	vca.GetGainInput()->Connect(envelope.GetOutput());
	vca.GetInput()->Connect(mixer.GetOutput());
	outputLevel.GetInput()->Connect(vca.GetOutput());
	waveWriter.GetInput()->Connect(outputLevel.GetOutput());

	logger.GetInput()->Connect(sequencer.GetFrequencyOutput());

	ModuleRunner runner(&waveWriter);

	auto update = [&]() {runner.Run(static_cast<int>(duration * fs)); };

	auto runTime = MeasureRunTimeInSeconds(update);

	waveWriter.Close();
	
	logger.WriteCsv("Log.csv");

	std::cout << "Performance: " << duration/runTime << " x faster than real time" << std::endl;
}
