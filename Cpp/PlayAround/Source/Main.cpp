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
#include "MoogFilter.h"

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
		SequencerEvent("C4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("C4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("C4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("E4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("F4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("E4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("E4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("D4", 1.0 / 8, 1.5 / 16, 1.0),
		SequencerEvent("C4", 1.0 / 4, 3.5 / 16, 1.0),
		}, -20);

	Gain vcoGain;
	Gain vca;
	MoogFilter vcf;
	Gain filterEnvelopeAmount;
	Sum mixer(2);
	EnvelopeGenerator envelope(ts);
	Lfo lfo(fs);
	Sum generatorTwoFrequency(2);

	vcoGain.GetGainInput()->Set(0.5);
	vcf.GetResonanceInput()->Set(0.1);
	vca.GetGainInput()->Set(1.0);

	filterEnvelopeAmount.GetGainInput()->Set(0.2);

	lfo.GetAmplitudeInput()->Set(100);
	lfo.GetOffsetInput()->Set(200);
	lfo.GetFrequencyInput()->Set(0.5);

	envelope.SustainInput()->Set(0.07);
	envelope.ReleaseInput()->Set(5e-2);
	envelope.DecayInput()->Set(0.1);
	SignalSink logger;

	generatorTwoFrequency.GetInputPort(0)->Connect(sequencer.GetFrequencyOutput());
	//generatorTwoFrequency.GetInputPort(1)->Connect(lfo.GetOutput());

	generatorOne.GetFrequencyInput()->Connect(sequencer.GetFrequencyOutput());
	generatorTwo.GetFrequencyInput()->Connect(generatorTwoFrequency.GetOutput());
	vcoGain.GetInput()->Connect(generatorTwo.GetOutput());
	//generatorTwo.GetPhaseResetInput()->Connect(generatorOne.GetOutput());
	//mixer.GetInputPort(0)->Connect(generatorOne.GetOutput());
	vcf.GetInput()->Connect(vcoGain.GetOutput());
	filterEnvelopeAmount.GetInput()->Connect(envelope.GetOutput());
	vcf.GetFrequencyInput()->Connect(filterEnvelopeAmount.GetOutput());
	mixer.GetInputPort(1)->Connect(vcf.GetOutput());
	envelope.GateInput()->Connect(sequencer.GetGateOutput());
	//vca.GetGainInput()->Connect(envelope.GetOutput());
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
