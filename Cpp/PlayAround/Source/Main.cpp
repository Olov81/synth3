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
#include "MulltiOscillator.h"

template<class F>
double MeasureRunTimeInSeconds(const F& f)
{
	const auto begin = std::chrono::steady_clock::now();
	f();
	const auto end = std::chrono::steady_clock::now();

	const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	return microseconds * 1e-6;
}

Sequencer::EventList GubbenNoak()
{
	return {
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
	};
}

SequencerEvent Event(const char* note, double value)
{
	return SequencerEvent(note, value, 0.9 * value, 1.0);
}

Sequencer::EventList LarsJansson()
{
	return {
		Event("C4", 1.0 / 8),
		Event("A4", 1.0),
		Event("D5", 1.0 / 4),
		Event("D5", 1.0 / 8),
		Event("Bb4", 1.0 / 4),
		Event("F4", 1.0 / 4),
		Event("E5", 9.0 / 8),
		Event("E5", 1.0 / 4),
		Event("E5", 1.0 / 8),
		Event("C#5", 1.0 / 4),
		Event("A4", 1.0 / 4),
		Event("F5", 5.0 / 8),
		Event("E5", 2.0 / 4),
		Event("D5", 3.0 / 8),
		Event("C5", 4.0 / 8),
		Event("Bb4", 1.0 / 16),
		Event("A4", 1.0 / 16),
		Event("Bb4", 2.0 / 8),
		Event("A4", 1.0 / 8),
		Event("Bb4", 1.0 / 4),
		Event("F5", 1.0 / 4),
		Event("A4", 2.0 / 4),
		Event("G4", 2.0 / 4),
		Event("F4", 1.0)
	};
}

Sequencer::EventList Metronome()
{
	static const size_t BEATS = 30;

	Sequencer::EventList eventList;

	for(size_t n = 0; n < BEATS; ++n)
	{
		const auto note = n % 4 == 0 ? "C7" : "C6";

		eventList.push_back(SequencerEvent(note, 1.0 / 4, 0.05 * 1.0 / 4, 1.0));
	}

	return eventList;
}

int main()
{
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 18;

	WaveWriter waveWriter("Apa.wav");

	//MultiOscillator multiOscillator(2, Waveforms::Sawtooth());
	WaveformGenerator generatorOne(Waveforms::Sawtooth());
	MultiOscillator generatorTwo(4, Waveforms::Sawtooth());
	//generatorTwo.GetTuneInput()->Set(11.95);
	
	Gain outputLevel;
	outputLevel.GetGainInput()->Set(0.2);

	Sequencer metronome(ts, 120, Metronome(), 0);
	Sequencer sequencer(ts, 120, LarsJansson(), 0);

	Gain vcoGain;
	Gain vca;
	Gain metronomeGain;
	MoogFilter vcf;
	Gain filterEnvelopeAmount;
	Gain pitchEnvelopeAmount;
	Sum filterFrequencyMixer(2);
	Sum mixer(2);
	EnvelopeGenerator envelope(ts);
	EnvelopeGenerator amplitudeEnvelope(ts);
	Lfo lfo(fs);
	Sum generatorTwoFrequency(2);

	vcoGain.GetGainInput()->Set(0.5);
	vcf.GetResonanceInput()->Set(0.1);
	vca.GetGainInput()->Connect(amplitudeEnvelope.GetOutput());

	filterEnvelopeAmount.GetInput()->Connect(envelope.GetOutput());
	filterFrequencyMixer.GetInputPort(0)->Connect(filterEnvelopeAmount.GetOutput());
	filterFrequencyMixer.GetInputPort(1)->Set(0.07);

	filterEnvelopeAmount.GetGainInput()->Set(0.1);
	pitchEnvelopeAmount.GetGainInput()->Set(0);

	lfo.GetAmplitudeInput()->Set(0.5);
	lfo.GetOffsetInput()->Set(0);
	lfo.GetFrequencyInput()->Set(6.0);

	amplitudeEnvelope.SustainInput()->Set(0);
	amplitudeEnvelope.ReleaseInput()->Set(0.5);
	amplitudeEnvelope.DecayInput()->Set(2.0);
	amplitudeEnvelope.AttackInput()->Set(0.01);
	amplitudeEnvelope.GateInput()->Connect(sequencer.GateOutput());

	envelope.SustainInput()->Set(0);
	envelope.ReleaseInput()->Set(5e-2);
	envelope.DecayInput()->Set(0.5);
	envelope.AttackInput()->Set(0.01);
	SignalSink logger;

	pitchEnvelopeAmount.GetInput()->Connect(envelope.GetOutput());

	generatorTwoFrequency.GetInputPort(0)->Connect(sequencer.PitchOutput());
	generatorTwoFrequency.GetInputPort(1)->Connect(lfo.GetOutput());

	generatorOne.FrequencyInput()->Connect(metronome.PitchOutput());
	metronomeGain.GetGainInput()->Connect(metronome.GateOutput());
	metronomeGain.GetInput()->Connect(generatorOne.GetOutput());

	generatorTwo.PitchInput()->Connect(generatorTwoFrequency.Output());
	vcoGain.GetInput()->Connect(generatorTwo.Output());
	//generatorTwo.GetPhaseResetInput()->Connect(generatorOne.Output());
	//mixer.GetInputPort(0)->Connect(metronomeGain.Output());
	vcf.GetInput()->Connect(vcoGain.GetOutput());
	vcf.GetFrequencyInput()->Connect(filterFrequencyMixer.Output());
	mixer.GetInputPort(1)->Connect(vcf.GetOutput());
	envelope.GateInput()->Connect(sequencer.GateOutput());
	//vca.GetGainInput()->Connect(envelope.Output());
	vca.GetInput()->Connect(mixer.Output());
	outputLevel.GetInput()->Connect(vca.GetOutput());
	waveWriter.GetInput()->Connect(outputLevel.GetOutput());

	logger.GetInput()->Connect(sequencer.PitchOutput());

	ModuleRunner runner(&waveWriter);

	auto update = [&]() {runner.Run(static_cast<int>(duration * fs)); };

	auto runTime = MeasureRunTimeInSeconds(update);

	waveWriter.Close();
	
	logger.WriteCsv("Log.csv");

	std::cout << "Performance: " << duration/runTime << " x faster than real time" << std::endl;
}
