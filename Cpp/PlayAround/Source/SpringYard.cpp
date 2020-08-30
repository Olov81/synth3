#include "SpringYard.h"
#include "DrumMachine.h"
#include "Megadrive.h"
#include "MidiFilePlayer.h"
#include "WaveWriter.h"
#include "Ym2612Channel.h"
#include "Framework/ModuleRunner.h"

static void ConfigureDrums(DrumMachine& dac, MidiDrumTrack& drumTrack)
{
	auto& snare = dac.GetChannel(0);
	snare.LoadSample("Samples/Sonic 1 Snare.wav");
	snare.GateInput()->Connect(drumTrack.GetGateOutput(38));

	auto& kick = dac.GetChannel(1);
	kick.LoadSample("Samples/Sonic 1 Kick.wav");
	kick.GateInput()->Connect(drumTrack.GetGateOutput(36));
	kick.GainInput()->Set(1.5);

	auto& hihatOne = dac.GetChannel(2);
	hihatOne.LoadSample("Samples/Sonic 1 Hi-Hat 1.wav");
	hihatOne.GateInput()->Connect(drumTrack.GetGateOutput(42));
	hihatOne.GainInput()->Set(0.5);

	auto& hihatTwo = dac.GetChannel(3);
	hihatTwo.LoadSample("Samples/Sonic 1 Hi-Hat 1.wav");
	hihatTwo.GateInput()->Connect(drumTrack.GetGateOutput(46));
	hihatTwo.GainInput()->Set(0.5);

	dac.GainInput()->Set(1.5);
}

static void ConfigureBass(Ym2612Channel& channel, MidiTrack& track)
{
	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmZero);
	
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(1.0);

	channel.ModulatorOne().GainInput()->Set(0.08);
	channel.ModulatorOne().RateInput()->Set(7.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.2);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.05);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);

	channel.CarrierOne().GainInput()->Set(0.35);
	channel.CarrierOne().RateInput()->Set(0.5);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.2);
	channel.CarrierOne().Envelope().DecayInput()->Set(0.5);
	channel.CarrierOne().Envelope().AttackInput()->Set(5e-4);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.01);

	channel.ModulatorTwo().GainInput()->Set(1.0);
	channel.ModulatorTwo().RateInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.0);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(5e-4);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(0.01);

	channel.CarrierTwo().GainInput()->Set(0.5);
	channel.CarrierTwo().RateInput()->Set(1.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.8);
	channel.CarrierTwo().Envelope().DecayInput()->Set(0.05);
	channel.CarrierTwo().Envelope().AttackInput()->Set(5e-4);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.03);
}

static void ConfigureBrass(Ym2612Channel& channel, MidiTrack& track, double detune, double pan)
{
	track.SetTranspose(0);

	channel.DetuneInput()->Set(detune);
	channel.PanInput()->Set(pan);
	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFive);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.3);

	channel.ModulatorOneFeedbackInput()->Set(1.0);
	channel.ModulatorOne().GainInput()->Set(1.0);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.5);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.8);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);

	channel.CarrierOne().GainInput()->Set(0.1);
	channel.CarrierOne().RateInput()->Set(2);
	channel.CarrierOne().Envelope().SustainInput()->Set(1.0);
	channel.CarrierOne().Envelope().DecayInput()->Set(1.0);
	channel.CarrierOne().Envelope().AttackInput()->Set(0.15);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.1);
	
	channel.ModulatorTwo().GainInput()->Set(0.1);
	channel.ModulatorTwo().RateInput()->Set(2);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(0.15);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(0.1);

	channel.CarrierTwo().GainInput()->Set(0.1);
	channel.CarrierTwo().RateInput()->Set(2);
	channel.CarrierTwo().Envelope().SustainInput()->Set(1.0);
	channel.CarrierTwo().Envelope().DecayInput()->Set(1.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(0.15);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.1);
}

static void ConfigureMelody(Ym2612Channel& channel, MidiTrack& track)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFour);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.25);
	channel.Vibrato().AmplitudeInput()->Set(0.25);
	channel.Vibrato().DelayInput()->Set(0.13);
	channel.Vibrato().FrequencyInput()->Set(5.5);
	
	channel.ModulatorOneFeedbackInput()->Set(0.9);
	channel.ModulatorOne().GainInput()->Set(0.9);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.2);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.5);
	channel.ModulatorOne().Envelope().AttackInput()->Set(2e-2);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1.0);

	channel.CarrierOne().GainInput()->Set(1.0);
	channel.CarrierOne().RateInput()->Set(2);
	channel.CarrierOne().Envelope().SustainInput()->Set(1.0);
	channel.CarrierOne().Envelope().DecayInput()->Set(1.0);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-2);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.1);

	channel.ModulatorTwo().GainInput()->Set(1.0);
	channel.ModulatorTwo().RateInput()->Set(0.5 * 1.001);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(2e-2);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1.0);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(0.5 * 1.001);
	channel.CarrierTwo().Envelope().SustainInput()->Set(1.0);
	channel.CarrierTwo().Envelope().DecayInput()->Set(1.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-2);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.1);
}

static void ConfigureIntro(Ym2612Channel& channel, MidiTrack& track, double detune, double pan)
{
	track.SetTranspose(12);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFour);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.15);
	channel.DetuneInput()->Set(detune);
	channel.PanInput()->Set(pan);
	
	channel.PitchEnvelope().DecayInput()->Set(0.025);
	channel.PitchEnvelope().GainInput()->Set(3.0);
	
	channel.ModulatorOneFeedbackInput()->Set(0.5);
	channel.ModulatorOne().GainInput()->Set(0.7);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.5);
	channel.ModulatorOne().Envelope().SustainInput()->Set(1.0);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1e-3);

	channel.CarrierOne().GainInput()->Set(1.0);
	channel.CarrierOne().RateInput()->Set(1.0);
	channel.CarrierOne().Envelope().SustainInput()->Set(1.0);
	channel.CarrierOne().Envelope().DecayInput()->Set(1.0);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(1e-3);

	channel.ModulatorTwo().GainInput()->Set(0.7);
	channel.ModulatorTwo().RateInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1e-3);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(1.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(1.0);
	channel.CarrierTwo().Envelope().DecayInput()->Set(1.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(1e-3);
}

static void ConfigureBell(Ym2612Channel& channel, MidiTrack& track)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFour);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.15);

	channel.ModulatorOneFeedbackInput()->Set(0.0);
	channel.ModulatorOne().GainInput()->Set(0.5);
	channel.ModulatorOne().RateInput()->Set(7.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.3);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.3);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1.0);

	channel.CarrierOne().GainInput()->Set(1.0);
	channel.CarrierOne().RateInput()->Set(2.005);
	channel.CarrierOne().Envelope().SustainInput()->Set(1.0);
	channel.CarrierOne().Envelope().DecayInput()->Set(1.0);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.2);

	channel.ModulatorTwo().GainInput()->Set(0.5);
	channel.ModulatorTwo().RateInput()->Set(7.0);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.3);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.3);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1.0);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(9.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(1.0);
	channel.CarrierTwo().Envelope().DecayInput()->Set(1.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.2);
}

static void ConfigureStabs(Ym2612Channel& channel, MidiTrack& track)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmTwo);
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.15);

	channel.ModulatorOneFeedbackInput()->Set(0.7);
	channel.ModulatorOne().GainInput()->Set(0.7);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.01);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.7);
	channel.ModulatorOne().Envelope().AttackInput()->Set(2e-2);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(1e-2);

	channel.CarrierOne().GainInput()->Set(0.5);
	channel.CarrierOne().RateInput()->Set(1.0);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.5);
	channel.CarrierOne().Envelope().DecayInput()->Set(0.3);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-2);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(1e-2);

	channel.ModulatorTwo().GainInput()->Set(0.6);
	channel.ModulatorTwo().RateInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.3);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(1e-2);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(1e-2);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(2.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.9);
	channel.CarrierTwo().Envelope().DecayInput()->Set(1.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(1e-2);
}

static void ConfigureSquare(PsgToneChannel& channel, MidiTrack& track)
{
	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.Envelope().AttackInput()->Set(0.1);
	channel.Envelope().SustainInput()->Set(1.0);
	channel.VolumeInput()->Set(0.2);
	channel.DetuneInput()->Set(0);
}

void SpringYard()
{
	static const int fs = 44100;
	static const double ts = 1.0 / fs;
	static const double duration = 45;

	MidiFilePlayer midiFilePlayer("SpringYard.mid", ts, 1.0, 2.0);
	auto bassTrack = midiFilePlayer.CreateTrack(8);
	auto brassTrack = midiFilePlayer.CreateTrack(5);
	auto melodyTrack = midiFilePlayer.CreateTrack(2);
	auto introTrack = midiFilePlayer.CreateTrack(7);
	auto bellTrack = midiFilePlayer.CreateTrack(10);
	auto stabsTrack = midiFilePlayer.CreateTrack(3);
	auto drumTrack = midiFilePlayer.CreateDrumTrack(9);
	
	Megadrive megadrive(ts, 8, 4);

	ConfigureDrums(megadrive.Dac(), drumTrack);
	ConfigureBass(megadrive.FmChannel(0), bassTrack);
	ConfigureBrass(megadrive.FmChannel(1), brassTrack, -0.05, -1);
	ConfigureBrass(megadrive.FmChannel(2), brassTrack, 0.05, 1);
	ConfigureMelody(megadrive.FmChannel(3), melodyTrack);
	ConfigureIntro(megadrive.FmChannel(4), introTrack, 0, -1);
	ConfigureIntro(megadrive.FmChannel(5), introTrack, 0.1, 1);
	ConfigureBell(megadrive.FmChannel(6), bellTrack);
	ConfigureStabs(megadrive.FmChannel(7), stabsTrack);
	ConfigureSquare(megadrive.Psg().ChannelOne(), brassTrack);
	
	WaveWriter waveWriter("SpringYard.wav", fs);

	waveWriter.LeftInput()->Connect(megadrive.LeftOutput());
	waveWriter.RightInput()->Connect(megadrive.RightOutput());

	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));

	waveWriter.Close();
}
