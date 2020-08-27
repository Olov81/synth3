#include "WaveWriter.h"
#include "WaveformGenerator.h"
#include "Framework/ModuleRunner.h"
#include "Lfo.h"
#include "Gain.h"
#include <chrono>

#include "DrumMachine.h"
#include "Sequencer.h"
#include "SignalSink.h"
#include "EnvelopeGenerator.h"
#include "FmOperator.h"
#include "MidiFilePlayer.h"
#include "Sum.h"
#include "MoogFilter.h"
#include "MulltiOscillator.h"
#include "Multiply.h"
#include "MasterSystemPsg.h"
#include "Megadrive.h"
#include "NesPsg.h"
#include "PulseGenerator.h"
#include "SpringYard.h"
#include "Ym2612Channel.h"
#include "../GreenHill.h"

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
		SequencerEvent("E5", 2.0 / 4, 0.9*2.0/4, 1.0, 0.1),
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
		SequencerEvent("Bb4", 1.0 / 8, 1.0 / 8, 1.0, 0.01),
		SequencerEvent("G4", 3.0 / 8, 0.99*3.0 / 8, 1.0),
		SequencerEvent("Eb4", 1.0 / 8,1.0 / 8, 1.0, 0.01),
		Event("F4", 1.0 / 8),
		Event("G4", 6.0 / 32),
		Event("Ab4", 1.0 / 32),
		SequencerEvent("G4", 1.0 / 32, 1.0 / 32, 1.0),
		SequencerEvent("F4", 1.0 / 4, 0.9* 1.0 / 4, 1.0, 0.01),
		Event("G4", 2.0 / 4)
	};
}

Sequencer::EventList Reflex()
{
	return {
		Event("E4", 1.0 / 8),
		Event("F#4", 1.0 / 8),
		SequencerEvent("G4", 1.0 / 8, 1.0 / 8, 1.0),
		Event("F#4", 1.0 / 8),
		SequencerEvent("G4", 1.0 / 8, 1.0 / 8, 1.0),
		Event("F#4", 1.0 / 8),
		Event("G4", 0.2 * 1.0 / 4),
		SequencerEvent("A4", 0.8 * 1.0 / 4,  0.9 * 0.8 * 1.0 / 4, 1.0, 0.02),
		SequencerEvent("B3", 1.0, 0.99*1.0, 1.0, 0.005),
		Event("A4", 1.0 / 8),
		Event("B4", 1.0 / 8),
		SequencerEvent("C5", 1.0 / 8, 1.0 / 8, 1.0),
		Event("B4", 1.0 / 8),
		SequencerEvent("C5", 1.0 / 8, 1.0 / 8, 1.0),
		Event("B4", 1.0 / 8),
		SequencerEvent("C5", 1.0 / 32, 1.0 / 32, 1.0),
		SequencerEvent("D5", 3.0 / 32, 3.0 / 32, 1.0, 0.05),
		SequencerEvent("C5", 1.0 / 8, 0.99*1.0 / 8, 1.0, 0.11),
		SequencerEvent("E4", 1.0, 1.0, 1.0, 0.002),
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

void ScrapBrain()
{
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 54;

	MidiFilePlayer midiFilePlayer("ScrapBrain.mid", ts);
	auto trackOne = midiFilePlayer.CreateTrack(1);
	auto trackTwo = midiFilePlayer.CreateTrack(2);
	auto trackThree = midiFilePlayer.CreateTrack(10);
	auto trackFour = midiFilePlayer.CreateTrack(5);
	
	MasterSystemPsg psg(fs);
	
	psg.ChannelOne().PitchInput()->Connect(trackOne.GetVoice(0).PitchOutput());
	psg.ChannelOne().GateInput()->Connect(trackOne.GetVoice(0).GateOutput());
	//psg.ChannelOne().VolumeInput()->Connect(trackOne.GetMidiControlOutput(7));
	psg.ChannelOne().VolumeInput()->Set(0.9);
	psg.ChannelOne().Vibrato().AmplitudeInput()->Connect(trackOne.GetMidiControlOutput(1));
	psg.ChannelOne().Vibrato().FrequencyInput()->Set(7.0);
	psg.ChannelOne().Envelope().AttackInput()->Set(0.001);
	psg.ChannelOne().Envelope().DecayInput()->Set(0.1);
	psg.ChannelOne().Envelope().SustainInput()->Set(0.4);
	psg.ChannelOne().Envelope().ReleaseInput()->Set(0.02);

	psg.ChannelTwo().PitchInput()->Connect(trackTwo.GetVoice(0).PitchOutput());
	psg.ChannelTwo().GateInput()->Connect(trackTwo.GetVoice(0).GateOutput());
	//psg.ChannelTwo().VolumeInput()->Connect(trackTwo.GetMidiControlOutput(7));
	psg.ChannelTwo().VolumeInput()->Set(1.0);
	psg.ChannelTwo().Vibrato().FrequencyInput()->Set(7.0);
	psg.ChannelTwo().Envelope().AttackInput()->Set(0.003);
	psg.ChannelTwo().Envelope().DecayInput()->Set(0.1);
	psg.ChannelTwo().Envelope().SustainInput()->Set(0.3);
	psg.ChannelTwo().Envelope().ReleaseInput()->Set(0.04);

	psg.ChannelThree().PitchInput()->Connect(trackThree.GetVoice(0).PitchOutput());
	psg.ChannelThree().GateInput()->Connect(trackThree.GetVoice(0).GateOutput());
	//psg.ChannelThree().VolumeInput()->Connect(trackThree.GetMidiControlOutput(7, 0.8));
	psg.ChannelThree().VolumeInput()->Set(0.9);
	psg.ChannelThree().DetuneInput()->Set(0.15);
	psg.ChannelThree().Vibrato().FrequencyInput()->Set(7.0);
	psg.ChannelThree().Envelope().AttackInput()->Set(0.001);
	psg.ChannelThree().Envelope().DecayInput()->Set(0.1);
	psg.ChannelThree().Envelope().SustainInput()->Set(0.5);
	psg.ChannelThree().Envelope().ReleaseInput()->Set(0.02);

	psg.ChannelFour().GateInput()->Connect(trackFour.GetVoice(0).GateOutput());
	psg.ChannelFour().Envelope().AttackInput()->Set(0.001);
	psg.ChannelFour().Envelope().DecayInput()->Set(0.1);
	psg.ChannelFour().Envelope().SustainInput()->Set(0.2);
	psg.ChannelFour().Envelope().ReleaseInput()->Set(0.02);
	
	WaveWriter waveWriter("ScrapBrain.wav");
	SignalSink logger;
	
	waveWriter.LeftInput()->Connect(psg.Output());
	waveWriter.RightInput()->Connect(psg.Output());
	logger.GetInput()->Connect(trackThree.GetMidiControlOutput(7));
	
	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));

	logger.WriteCsv("MidiLog.csv");
	waveWriter.Close();
}

void GreenHillMasterSystem()
{
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 54;

	MidiFilePlayer midiFilePlayer("GreenHill.mid", ts);
	auto trackOne = midiFilePlayer.CreateTrack(1);
	auto trackTwo = midiFilePlayer.CreateTrack(2);
	auto trackThree = midiFilePlayer.CreateTrack(3);
	auto trackFour = midiFilePlayer.CreateTrack(4);

	MasterSystemPsg psg(fs);

	psg.ChannelOne().PitchInput()->Connect(trackOne.GetVoice(0).PitchOutput());
	psg.ChannelOne().GateInput()->Connect(trackOne.GetVoice(0).GateOutput());
	psg.ChannelOne().VolumeInput()->Connect(trackOne.GetMidiControlOutput(7));
	//psg.ChannelOne().VolumeInput()->Set(0.9);
	psg.ChannelOne().Vibrato().AmplitudeInput()->Connect(trackOne.GetMidiControlOutput(1));
	psg.ChannelOne().Vibrato().FrequencyInput()->Set(7.0);
	psg.ChannelOne().Envelope().AttackInput()->Set(0.001);
	psg.ChannelOne().Envelope().DecayInput()->Set(0.1);
	psg.ChannelOne().Envelope().SustainInput()->Set(0.4);
	psg.ChannelOne().Envelope().ReleaseInput()->Set(0.02);

	psg.ChannelTwo().PitchInput()->Connect(trackTwo.GetVoice(0).PitchOutput());
	psg.ChannelTwo().GateInput()->Connect(trackTwo.GetVoice(0).GateOutput());
	psg.ChannelTwo().VolumeInput()->Connect(trackTwo.GetMidiControlOutput(7));
	//psg.ChannelTwo().VolumeInput()->Set(0.0);
	psg.ChannelTwo().Vibrato().FrequencyInput()->Set(7.0);
	psg.ChannelTwo().Envelope().AttackInput()->Set(0.003);
	psg.ChannelTwo().Envelope().DecayInput()->Set(0.1);
	psg.ChannelTwo().Envelope().SustainInput()->Set(0.3);
	psg.ChannelTwo().Envelope().ReleaseInput()->Set(0.04);

	psg.ChannelThree().PitchInput()->Connect(trackThree.GetVoice(0).PitchOutput());
	psg.ChannelThree().GateInput()->Connect(trackThree.GetVoice(0).GateOutput());
	psg.ChannelThree().VolumeInput()->Connect(trackThree.GetMidiControlOutput(7, 0.8));
	//psg.ChannelThree().VolumeInput()->Set(0.0);
	psg.ChannelThree().DetuneInput()->Set(0.12);
	psg.ChannelThree().Vibrato().FrequencyInput()->Set(7.0);
	psg.ChannelThree().Envelope().AttackInput()->Set(0.001);
	psg.ChannelThree().Envelope().DecayInput()->Set(0.1);
	psg.ChannelThree().Envelope().SustainInput()->Set(0.5);
	psg.ChannelThree().Envelope().ReleaseInput()->Set(0.02);

	psg.ChannelFour().GateInput()->Connect(trackFour.GetVoice(0).GateOutput());
	//psg.ChannelFour().()->Connect(trackFour.GetMidiControlOutput(7, 0.8));
	psg.ChannelFour().Envelope().AttackInput()->Set(0.001);
	psg.ChannelFour().Envelope().DecayInput()->Set(0.15);
	psg.ChannelFour().Envelope().SustainInput()->Set(0.1);
	psg.ChannelFour().Envelope().ReleaseInput()->Set(0.01);

	WaveWriter waveWriter("GreenHill.wav");
	SignalSink logger;

	waveWriter.LeftInput()->Connect(psg.Output());
	waveWriter.RightInput()->Connect(psg.Output());
	logger.GetInput()->Connect(trackThree.GetMidiControlOutput(7));

	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));

	logger.WriteCsv("MidiLog.csv");
	waveWriter.Close();
}

void Mario()
{
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 80;

	MidiFilePlayer midiFilePlayer("Overworld.mid", ts);
	auto trackOne = midiFilePlayer.CreateTrack(1);
	auto trackTwo = midiFilePlayer.CreateTrack(2);
	auto trackThree = midiFilePlayer.CreateTrack(3);
	auto trackFour = midiFilePlayer.CreateTrack(4);

	NesPsg psg(fs);

	psg.SquareOne().PitchInput()->Connect(trackOne.GetVoice(0).PitchOutput());
	psg.SquareOne().GateInput()->Connect(trackOne.GetVoice(0).GateOutput());
	psg.SquareOne().VolumeInput()->Connect(trackOne.GetMidiControlOutput(7,0.8));
	psg.SquareOne().VolumeInput()->Set(0.0);
	psg.SquareOne().Vibrato().AmplitudeInput()->Connect(trackOne.GetMidiControlOutput(1));
	psg.SquareOne().Vibrato().FrequencyInput()->Set(7.0);
	psg.SquareOne().Envelope().AttackInput()->Set(0.005);
	psg.SquareOne().Envelope().DecayInput()->Set(0.1);
	psg.SquareOne().Envelope().SustainInput()->Set(0.4);
	psg.SquareOne().Envelope().ReleaseInput()->Set(0.05);

	psg.SquareTwo().PitchInput()->Connect(trackTwo.GetVoice(0).PitchOutput());
	psg.SquareTwo().GateInput()->Connect(trackTwo.GetVoice(0).GateOutput());
	psg.SquareTwo().VolumeInput()->Connect(trackTwo.GetMidiControlOutput(7, 0.8));
	psg.SquareTwo().VolumeInput()->Set(0.0);
	psg.SquareTwo().Vibrato().FrequencyInput()->Set(7.0);
	psg.SquareTwo().Envelope().AttackInput()->Set(0.005);
	psg.SquareTwo().Envelope().DecayInput()->Set(0.1);
	psg.SquareTwo().Envelope().SustainInput()->Set(0.4);
	psg.SquareTwo().Envelope().ReleaseInput()->Set(0.05);

	psg.Triangle().PitchInput()->Connect(trackThree.GetVoice(0).PitchOutput());
	psg.Triangle().GateInput()->Connect(trackThree.GetVoice(0).GateOutput());
	psg.Triangle().VolumeInput()->Connect(trackThree.GetMidiControlOutput(7, 1.0));
	//psg.ChannelThree().VolumeInput()->Set(0.0);
	psg.Triangle().DetuneInput()->Set(0.12);
	psg.Triangle().Vibrato().FrequencyInput()->Set(7.0);
	psg.Triangle().Envelope().AttackInput()->Set(0.001);
	psg.Triangle().Envelope().DecayInput()->Set(0.1);
	psg.Triangle().Envelope().SustainInput()->Set(1.0);
	psg.Triangle().Envelope().ReleaseInput()->Set(0.02);

	//psg.Noise().GateInput()->Connect(trackFour.GateOutput());
	psg.Noise().Envelope().AttackInput()->Set(0.001);
	psg.Noise().Envelope().DecayInput()->Set(0.1);
	psg.Noise().Envelope().SustainInput()->Set(0.1);
	psg.Noise().Envelope().ReleaseInput()->Set(0.01);

	WaveWriter waveWriter("Mario.wav");
	SignalSink logger;

	waveWriter.LeftInput()->Connect(psg.Output());
	waveWriter.RightInput()->Connect(psg.Output());
	logger.GetInput()->Connect(trackThree.GetMidiControlOutput(7));

	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));

	logger.WriteCsv("MidiLog.csv");
	waveWriter.Close();
}

void TestFm()
{
	const double fs = 44100;
	const double ts = 1 / fs;
	const double duration = 5;
	
	Megadrive megadrive(ts, 1, 1);
	megadrive.GainInput()->Set(0.5);

	auto& channel = megadrive.FmChannel(0);

	channel.GateInput()->Set(1.0);
	channel.PitchInput()->Set(0);
	channel.GainInput()->Set(1.0);
	
	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFour);
	channel.CarrierTwo().GainInput()->Set(0.0);

	channel.CarrierOne().GainInput()->Set(1.0);
	channel.CarrierOne().RateInput()->Set(1.0);
	channel.CarrierOne().Envelope().SustainInput()->Set(1.0);
	
	channel.ModulatorOne().GainInput()->Set(1.0);
	channel.ModulatorOne().RateInput()->Set(4.0);
	channel.ModulatorOne().Envelope().SustainInput()->Set(1.0);

	WaveWriter waveWriter("FmTest.wav");

	waveWriter.LeftInput()->Connect(megadrive.LeftOutput());
	waveWriter.RightInput()->Connect(megadrive.RightOutput());
	
	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));
	
	waveWriter.Close();
}

int main()
{
	ScrapBrain();

	return 0;
	
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 10;

	WaveWriter waveWriter("Apa.wav");

	MultiOscillator generatorTwo(2, Waveforms::CustomOne(),12);
	generatorTwo.DetuneInput()->Set(0.03);

	//PulseGenerator generatorTwo;
	//generatorTwo.PulseWidthInput()->Set(0.1);

	Gain outputLevel;
	outputLevel.GetGainInput()->Set(0.2);

	Sequencer metronome(ts, 130, Metronome(), 0);
	Sequencer sequencer(ts, 112, Reflex(), 0);

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
	Lfo pwm(fs);
	Sum generatorTwoFrequency(2);

	vcoGain.GetGainInput()->Set(0.5);
	vcf.GetResonanceInput()->Set(0.1);
	vca.GetGainInput()->Connect(amplitudeEnvelope.Output());

	filterEnvelopeAmount.GetInput()->Connect(filterEnvelope.Output());
	filterFrequencyMixer.GetInputPort(0)->Connect(filterEnvelopeAmount.GetOutput());
	filterFrequencyMixer.GetInputPort(1)->Set(0.3);

	filterEnvelopeAmount.GetGainInput()->Set(0.2);
	pitchEnvelopeAmount.GetGainInput()->Set(0);

	lfo.AmplitudeInput()->Set(0.1);
	lfo.OffsetInput()->Set(0);
	lfo.FrequencyInput()->Set(8.0);
	lfo.DelayInput()->Set(0.4);
	lfo.GateInput()->Connect(sequencer.GateOutput());

	pwm.AmplitudeInput()->Set(0.45);
	pwm.OffsetInput()->Set(0.5);
	pwm.FrequencyInput()->Set(0.2);

	amplitudeEnvelope.SustainInput()->Set(0.0);
	amplitudeEnvelope.ReleaseInput()->Set(0.1);
	amplitudeEnvelope.DecayInput()->Set(2.0);
	amplitudeEnvelope.AttackInput()->Set(0.01);
	amplitudeEnvelope.GateInput()->Connect(sequencer.GateOutput());

	filterEnvelope.SustainInput()->Set(0);
	filterEnvelope.ReleaseInput()->Set(5e-2);
	filterEnvelope.DecayInput()->Set(0.1);
	filterEnvelope.AttackInput()->Set(0.03);
	SignalSink logger;

	pitchEnvelopeAmount.GetInput()->Connect(filterEnvelope.Output());

	generatorTwoFrequency.GetInputPort(0)->Connect(sequencer.PitchOutput());
	generatorTwoFrequency.GetInputPort(1)->Connect(lfo.Output());

	//generatorTwo.PulseWidthInput()->Connect(pwm.Output());
	//generatorTwo.PulseWidthInput()->Set(0.9);
	generatorTwo.PitchInput()->Connect(generatorTwoFrequency.Output());
	vcoGain.GetInput()->Connect(generatorTwo.Output());

	vcf.GetInput()->Connect(vcoGain.GetOutput());
	vcf.GetFrequencyInput()->Connect(filterFrequencyMixer.Output());
	mixer.GetInputPort(1)->Connect(vcf.GetOutput());
	filterEnvelope.GateInput()->Connect(sequencer.GateOutput());

	vca.GetInput()->Connect(mixer.Output());
	outputLevel.GetInput()->Connect(vca.GetOutput());
	waveWriter.LeftInput()->Connect(outputLevel.GetOutput());
	waveWriter.RightInput()->Connect(outputLevel.GetOutput());

	logger.GetInput()->Connect(sequencer.GateOutput());

	ModuleRunner runner(&waveWriter);

	auto update = [&]() {runner.Run(static_cast<int>(duration * fs)); };

	auto runTime = MeasureRunTimeInSeconds(update);

	waveWriter.Close();
	
	logger.WriteCsv("Log.csv");

	std::cout << "Performance: " << duration/runTime << " x faster than real time" << std::endl;
}
