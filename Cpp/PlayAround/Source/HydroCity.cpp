#include "HydroCity.h"

#include "Megadrive.h"
#include "MidiFilePlayer.h"
#include "SignalSink.h"
#include "WaveWriter.h"
#include "Framework/ModuleRunner.h"

static void ConfigureDrums(DrumMachine& dac, MidiDrumTrack& drumTrack)
{
	auto& snare = dac.GetChannel(0);
	snare.LoadSample("Samples/HydroCity Tom Snare.wav");
	snare.GateInput()->Connect(drumTrack.GetGateOutput(38));
	snare.GainInput()->Set(1.1);
	
	auto& kick = dac.GetChannel(1);
	kick.LoadSample("Samples/HydroCity Tom Kick2.wav");
	kick.GateInput()->Connect(drumTrack.GetGateOutput(35));
	kick.GainInput()->Set(1.7);

	auto& tomHigh = dac.GetChannel(2);
	tomHigh.LoadSample("Samples/HydroCity Tom High.wav");
	tomHigh.GateInput()->Connect(drumTrack.GetGateOutput(50));
	tomHigh.GainInput()->Set(2.0);

	auto& tomMid = dac.GetChannel(3);
	tomMid.LoadSample("Samples/HydroCity Tom Mid.wav");
	tomMid.GateInput()->Connect(drumTrack.GetGateOutput(45));
	tomMid.GainInput()->Set(1.5);

	auto& tomMid2 = dac.GetChannel(4);
	tomMid2.LoadSample("Samples/HydroCity Tom Mid 2.wav");
	tomMid2.GateInput()->Connect(drumTrack.GetGateOutput(43));
	tomMid2.GainInput()->Set(1.5);

	auto& tomMidLow = dac.GetChannel(5);
	tomMidLow.LoadSample("Samples/HydroCity Tom Low.wav");
	tomMidLow.GateInput()->Connect(drumTrack.GetGateOutput(41));
	tomMidLow.GainInput()->Set(2.0);

	auto& closedHihat = dac.GetChannel(6);
	closedHihat.LoadSample("Samples/Sonic 3/Sonic 3 Hi-Hat 3.wav");
	closedHihat.GateInput()->Connect(drumTrack.GetGateOutput(42));
	closedHihat.GainInput()->Set(0.3);

	auto& openHihat = dac.GetChannel(7);
	openHihat.LoadSample("Samples/Sonic 3/Sonic 3 Hi-Hat 4.wav");
	openHihat.GateInput()->Connect(drumTrack.GetGateOutput(46));
	openHihat.GainInput()->Set(1.0);
	
	dac.GainInput()->Set(1.5);
}

static void ConfigureMelody(Ym2612Channel& channel, MidiTrack& track, double detune, double gain)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFour);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(gain);
	channel.DetuneInput()->Set(detune);
	channel.Vibrato().AmplitudeInput()->Set(0.2);
	channel.Vibrato().DelayInput()->Set(0.4);
	channel.Vibrato().FrequencyInput()->Set(7);
	
	channel.ModulatorOneFeedbackInput()->Set(0.9);
	channel.ModulatorOne().GainInput()->Set(1.0);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.1);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.5);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-2);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1e-1);

	channel.CarrierOne().GainInput()->Set(0.9);
	channel.CarrierOne().RateInput()->Set(4);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.8);
	channel.CarrierOne().Envelope().DecayInput()->Set(0.1);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-2);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(1e-1);
	channel.CarrierOne().Envelope().VelocitySensitivity()->Set(0.0);
	
	channel.ModulatorTwo().GainInput()->Set(1.0);
	channel.ModulatorTwo().RateInput()->Set(2);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.7);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.1);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(1e-1);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1e-2);

	channel.CarrierTwo().GainInput()->Set(0.9);
	channel.CarrierTwo().RateInput()->Set(2);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.8);
	channel.CarrierTwo().Envelope().DecayInput()->Set(0.1);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-2);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(1e-1);
	channel.CarrierTwo().Envelope().VelocitySensitivity()->Set(0.0);
}

void ConfigureChords(Ym2612Channel& channel, MidiTrack& track)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmTwo);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.25);

	channel.ModulatorOneFeedbackInput()->Set(0.8);
	channel.ModulatorOne().GainInput()->Set(0.8);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.05);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.8);
	channel.ModulatorOne().Envelope().AttackInput()->Set(0.02);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1e-2);
	channel.ModulatorOne().Envelope().VelocitySensitivity()->Set(0);

	channel.CarrierOne().GainInput()->Set(0.1);	
	channel.CarrierOne().RateInput()->Set(7);
	channel.CarrierOne().Envelope().SustainInput()->Set(1);
	channel.CarrierOne().Envelope().DecayInput()->Set(0.5);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-2);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(5e-2);
	channel.CarrierOne().Envelope().VelocitySensitivity()->Set(0);

	channel.ModulatorTwo().GainInput()->Set(0.7);
	channel.ModulatorTwo().RateInput()->Set(1.0 * 1.001);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.8);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.05);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(0.02);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1e-2);
	channel.ModulatorTwo().Envelope().VelocitySensitivity()->Set(0);

	channel.CarrierTwo().GainInput()->Set(0.8);
	channel.CarrierTwo().RateInput()->Set(1 * 1.005);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0);
	channel.CarrierTwo().Envelope().DecayInput()->Set(0.5);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(5e-2);
	channel.CarrierTwo().Envelope().VelocitySensitivity()->Set(0);
}

void ConfigureSquare(PsgToneChannel& channel, MidiTrack& track, double detune)
{
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.Envelope().AttackInput()->Set(0.015);
	channel.Envelope().SustainInput()->Set(0);
	channel.Envelope().DecayInput()->Set(0.4);
	channel.Envelope().ReleaseInput()->Set(0.05);
	channel.VolumeInput()->Set(0.35);
	channel.DetuneInput()->Set(detune);
}

void ConfigureBass(Ym2612Channel& channel, MidiTrack& track)
{
	track.SetTranspose(12);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmZero);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.4);

	channel.ModulatorOneFeedbackInput()->Set(0.5);
	channel.ModulatorOne().GainInput()->Set(0.9);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.03);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.05);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1e-2);
	channel.ModulatorOne().Envelope().VelocitySensitivity()->Set(0);

	channel.CarrierOne().GainInput()->Set(0.8);
	channel.CarrierOne().RateInput()->Set(0.5);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.8);
	channel.CarrierOne().Envelope().DecayInput()->Set(0.03);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(1e-2);
	channel.CarrierOne().Envelope().VelocitySensitivity()->Set(0);

	channel.ModulatorTwo().GainInput()->Set(0.8);
	channel.ModulatorTwo().RateInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.25);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.05);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(2e-2);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1e-2);
	channel.ModulatorTwo().Envelope().VelocitySensitivity()->Set(0);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(1.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.8);
	channel.CarrierTwo().Envelope().DecayInput()->Set(0.05);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(1e-2);
	channel.CarrierTwo().Envelope().VelocitySensitivity()->Set(0);
}

void ConfigureBridgeMelody(Ym2612Channel& channel, MidiTrack& track, double detune, double gain)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmTwo);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(gain);
	channel.DetuneInput()->Set(detune);
	channel.Vibrato().AmplitudeInput()->Set(0.2);
	channel.Vibrato().DelayInput()->Set(0.2);
	channel.Vibrato().FrequencyInput()->Set(7);
	
	channel.ModulatorOneFeedbackInput()->Set(0.4);
	channel.ModulatorOne().GainInput()->Set(1.0);
	channel.ModulatorOne().RateInput()->Set(1.0 * 1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(2);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.1);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(0.1);

	channel.CarrierOne().GainInput()->Set(0.2);
	channel.CarrierOne().RateInput()->Set(5 * 1.0);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.1);
	channel.CarrierOne().Envelope().DecayInput()->Set(2);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.1);

	channel.ModulatorTwo().GainInput()->Set(0.5);
	channel.ModulatorTwo().RateInput()->Set(3.0 * 1.0);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.1);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(2);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(0.1);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(1 * 1.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.6);
	channel.CarrierTwo().Envelope().DecayInput()->Set(0.5);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.1);
	channel.CarrierTwo().Envelope().VelocitySensitivity()->Set(0.0);
}

void HydroCity()
{
	static const int fs = 44100;
	static const double ts = 1.0 / fs;
	static const double duration = 55;

	MidiFilePlayer midiFilePlayer("S3HydroCity2.mid", ts, 1.0, 0);
	auto melodyTrack = midiFilePlayer.CreateTrack(7);
	auto melodyTrackDelay = midiFilePlayer.CreateTrack(8);
	auto bridgeMelodyTrack = midiFilePlayer.CreateTrack(9);
	auto bridgeMelodyTrackDelay = midiFilePlayer.CreateTrack(10);
	auto chordTrackOne = midiFilePlayer.CreateTrack(4);
	auto chordTrackTwo = midiFilePlayer.CreateTrack(5);
	auto squareTrack = midiFilePlayer.CreateTrack(2);
	auto bassTrack = midiFilePlayer.CreateTrack(3);
	auto drumTrack = midiFilePlayer.CreateDrumTrack(1);

	Megadrive megadrive(ts, 7, 8);

	ConfigureDrums(megadrive.Dac(), drumTrack);
	ConfigureMelody(megadrive.FmChannel(0), melodyTrack, 0, 0.25);
	ConfigureMelody(megadrive.FmChannel(1), melodyTrackDelay, 0.12, 0.15);
	ConfigureChords(megadrive.FmChannel(2), chordTrackOne);
	ConfigureChords(megadrive.FmChannel(3), chordTrackTwo);
	ConfigureBass(megadrive.FmChannel(4), bassTrack);
	ConfigureBridgeMelody(megadrive.FmChannel(5), bridgeMelodyTrack, 0, 0.3);
	ConfigureBridgeMelody(megadrive.FmChannel(6), bridgeMelodyTrackDelay, 0.12, 0.2);
	ConfigureSquare(megadrive.Psg().ChannelOne(), squareTrack, 0.0);
	ConfigureSquare(megadrive.Psg().ChannelTwo(), squareTrack, 0.12);

	WaveWriter waveWriter("HydroCity.wav", fs);
	SignalSink logger;

	logger.GetInput()->Connect(static_cast<EnvelopeGenerator&>(megadrive.FmChannel(5).CarrierOne().Envelope()).Output());
	
	waveWriter.LeftInput()->Connect(megadrive.LeftOutput());
	waveWriter.RightInput()->Connect(megadrive.RightOutput());

	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));

	waveWriter.Close();
	logger.WriteCsv("HydroCity.csv");
}
