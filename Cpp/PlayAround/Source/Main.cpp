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
#include "EnvelopeFollower.h"

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

Sequencer::EventList TheBill()
{
	return {
		SequencerEvent("C4", 1.0 / 8, 1.0 / 8, 1.0),
		Event("Eb4", 1.0 / 8),
		Event("Bb4", 1.0 / 8),
		SequencerEvent("G4", 3.0 / 8, 1.0 / 8, 1.0),
		SequencerEvent("Eb4", 1.0 / 8, 1.0/8, 1.0),
		Event("F4", 1.0 / 8),
		Event("G4", 6.0 / 32),
		Event("Ab4", 1.0 / 32),
		Event("G4", 1.0 / 32),
		Event("F4", 1.0 / 4),
		Event("G4", 1.0 / 4)
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
	static const double duration = 6;

	WaveWriter waveWriter("Apa.wav");

	//MultiOscillator multiOscillator(2, Waveforms::Sawtooth());
	WaveformGenerator generatorOne(Waveforms::Sawtooth());
	MultiOscillator generatorTwo(4, Waveforms::Sawtooth());
	generatorTwo.DetuneInput()->Set(0.02);
	//generatorTwo.GetTuneInput()->Set(11.95);
	
	Gain outputLevel;
	outputLevel.GetGainInput()->Set(0.2);

	Sequencer metronome(ts, 130, Metronome(), 0);
	Sequencer sequencer(ts, 130, TheBill(), 9);
	EnvelopeFollower portamento(ts);
	portamento.TimeInput()->Set(0.005);

	Gain vcoGain;
	Gain vca;
	Gain metronomeGain;
	MoogFilter vcf;
	Gain filterEnvelopeAmount;
	Gain pitchEnvelopeAmount;
	Sum filterFrequencyMixer(2);
	Sum mixer(2);
	EnvelopeGenerator filterEnvelope(ts);
	EnvelopeGenerator amplitudeEnvelope(ts);
	Lfo lfo(fs);
	Sum generatorTwoFrequency(2);

	vcoGain.GetGainInput()->Set(0.5);
	vcf.GetResonanceInput()->Set(0.1);
	vca.GetGainInput()->Connect(amplitudeEnvelope.GetOutput());

	filterEnvelopeAmount.GetInput()->Connect(filterEnvelope.GetOutput());
	filterFrequencyMixer.GetInputPort(0)->Connect(filterEnvelopeAmount.GetOutput());
	filterFrequencyMixer.GetInputPort(1)->Set(0.3);

	filterEnvelopeAmount.GetGainInput()->Set(0.5);
	pitchEnvelopeAmount.GetGainInput()->Set(0);

	lfo.AmplitudeInput()->Set(0.3);
	lfo.OffsetInput()->Set(0);
	lfo.FrequencyInput()->Set(6.0);
	lfo.DelayInput()->Set(0.3);
	lfo.GateInput()->Connect(sequencer.GateOutput());

	amplitudeEnvelope.SustainInput()->Set(1.0);
	amplitudeEnvelope.ReleaseInput()->Set(1.0);
	amplitudeEnvelope.DecayInput()->Set(2.0);
	amplitudeEnvelope.AttackInput()->Set(0.03);
	amplitudeEnvelope.GateInput()->Connect(sequencer.GateOutput());

	filterEnvelope.SustainInput()->Set(0);
	filterEnvelope.ReleaseInput()->Set(5e-2);
	filterEnvelope.DecayInput()->Set(0.1);
	filterEnvelope.AttackInput()->Set(0.03);
	SignalSink logger;

	pitchEnvelopeAmount.GetInput()->Connect(filterEnvelope.GetOutput());

	portamento.GetInput()->Connect(sequencer.PitchOutput());
	generatorTwoFrequency.GetInputPort(0)->Connect(portamento.GetOutput());
	generatorTwoFrequency.GetInputPort(1)->Connect(lfo.GetOutput());

	generatorOne.FrequencyInput()->Connect(metronome.PitchOutput());
	metronomeGain.GetGainInput()->Connect(metronome.GateOutput());
	metronomeGain.GetInput()->Connect(generatorOne.GetOutput());

	generatorTwo.PitchInput()->Connect(generatorTwoFrequency.Output());
	vcoGain.GetInput()->Connect(generatorTwo.Output());
	//generatorTwo.GetPhaseResetInput()->Connect(generatorOne.Output());
	//mixer.GetInputPort(0)->Connect(metronomeGain.GetOutput());
	vcf.GetInput()->Connect(vcoGain.GetOutput());
	vcf.GetFrequencyInput()->Connect(filterFrequencyMixer.Output());
	mixer.GetInputPort(1)->Connect(vcf.GetOutput());
	filterEnvelope.GateInput()->Connect(sequencer.GateOutput());
	//vca.GetGainInput()->Connect(envelope.Output());
	vca.GetInput()->Connect(mixer.Output());
	outputLevel.GetInput()->Connect(vca.GetOutput());
	waveWriter.GetInput()->Connect(outputLevel.GetOutput());

	logger.GetInput()->Connect(sequencer.GateOutput());

	ModuleRunner runner(&waveWriter);

	auto update = [&]() {runner.Run(static_cast<int>(duration * fs)); };

	auto runTime = MeasureRunTimeInSeconds(update);

	waveWriter.Close();
	
	logger.WriteCsv("Log.csv");

	std::cout << "Performance: " << duration/runTime << " x faster than real time" << std::endl;
}
