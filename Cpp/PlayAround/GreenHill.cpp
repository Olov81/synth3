#include "GreenHill.h"

#include "ControlSignalGenerator.h"
#include "Megadrive.h"
#include "MidiFilePlayer.h"
#include "WaveWriter.h"
#include "Framework/ModuleRunner.h"

static void ConfigureDrums(DrumMachine& dac, MidiDrumTrack& drumTrack)
{
	dac.GainInput()->Set(1.5);
	
	auto& snare = dac.GetChannel(0);
	snare.LoadSample("Samples/Sonic 1 Snare.wav");
	snare.GateInput()->Connect(drumTrack.GetGateOutput(40));
	snare.GainInput()->Set(1.2);
	
	auto& kick = dac.GetChannel(1);
	kick.LoadSample("Samples/Sonic 1 Kick.wav");
	kick.GateInput()->Connect(drumTrack.GetGateOutput(35));
	kick.GainInput()->Set(1.5);

	auto& hihatOne = dac.GetChannel(2);
	hihatOne.LoadSample("Samples/Sonic 1 Hi-Hat 1.wav");
	hihatOne.GateInput()->Connect(drumTrack.GetGateOutput(42));
	hihatOne.GainInput()->Set(0.5);

	auto& hihatTwo = dac.GetChannel(3);
	hihatTwo.LoadSample("Samples/Sonic 1 Hi-Hat 2.wav");
	hihatTwo.GateInput()->Connect(drumTrack.GetGateOutput(46));
	hihatTwo.GainInput()->Set(0.5);
}

static void ConfigureBass(Ym2612Channel& channel, MidiTrack& track)
{
	track.SetTranspose(12);
	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmZero);

	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.8);

	channel.ModulatorOneFeedbackInput()->Set(0.1);
	channel.ModulatorOne().GainInput()->Set(0.1);
	channel.ModulatorOne().RateInput()->Set(10.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.1);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.3);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);

	channel.CarrierOne().GainInput()->Set(0.4);
	channel.CarrierOne().RateInput()->Set(0.5);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.5);
	channel.CarrierOne().Envelope().DecayInput()->Set(1.0);
	channel.CarrierOne().Envelope().AttackInput()->Set(5e-4);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.01);

	channel.ModulatorTwo().GainInput()->Set(0.8);
	channel.ModulatorTwo().RateInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.2);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.5);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(5e-4);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(0.01);

	channel.CarrierTwo().GainInput()->Set(0.5);
	channel.CarrierTwo().RateInput()->Set(0.5);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.8);
	channel.CarrierTwo().Envelope().DecayInput()->Set(1.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(5e-4);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.03);
}

static void ConfigureBrass(Ym2612Channel& channel, MidiTrack& track, size_t voice, double pan)
{
	track.SetTranspose(0);

	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmFour);
	channel.GateInput()->Connect(track.GetVoice(voice).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(voice).PitchOutput());
	channel.GainInput()->Set(0.17);
	channel.PitchEnvelope().DecayInput()->Set(0.02);
	channel.PanInput()->Set(pan);
	
	channel.ModulatorOneFeedbackInput()->Set(0.5);
	channel.ModulatorOne().GainInput()->Set(0.9);
	channel.ModulatorOne().RateInput()->Set(1.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.01);
	channel.ModulatorOne().Envelope().SustainInput()->Set(1.0);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(2e-1);

	channel.CarrierOne().GainInput()->Set(1.0);
	channel.CarrierOne().RateInput()->Set(1.0);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.3);
	channel.CarrierOne().Envelope().DecayInput()->Set(3.0);
	channel.CarrierOne().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(1.5e-1);

	channel.ModulatorTwo().GainInput()->Set(0.9);
	channel.ModulatorTwo().RateInput()->Set(1.005);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.3);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(2e-1);

	channel.CarrierTwo().GainInput()->Set(1.0);
	channel.CarrierTwo().RateInput()->Set(1.005); 
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.3);
	channel.CarrierTwo().Envelope().DecayInput()->Set(3.0);
	channel.CarrierTwo().Envelope().AttackInput()->Set(1e-3);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(1.5e-1);
}

static void ConfigureEP(Ym2612Channel& channel, MidiTrack& track, IInputPort* pPanTransformInput, IOutputPort* pPanTransformOutput)
{
	track.SetTranspose(0);

	pPanTransformInput->Connect(track.GetMidiControlOutput(10));
	channel.PanInput()->Connect(pPanTransformOutput);
	
	channel.SetAlgorithm(Ym2612Algorithm::AlgorithmSix);

	channel.GateInput()->Connect(track.GetVoice(0).GateOutput());
	channel.PitchInput()->Connect(track.GetVoice(0).PitchOutput());
	channel.GainInput()->Set(0.2);

	channel.ModulatorOneFeedbackInput()->Set(0.7);
	channel.ModulatorOne().GainInput()->Set(0.3);
	channel.ModulatorOne().RateInput()->Set(15.0);
	channel.ModulatorOne().Envelope().DecayInput()->Set(0.05);
	channel.ModulatorOne().Envelope().SustainInput()->Set(0.0);
	channel.ModulatorOne().Envelope().AttackInput()->Set(1e-3);
	channel.ModulatorOne().Envelope().ReleaseInput()->Set(0.01);

	channel.CarrierOne().GainInput()->Set(0.8);
	channel.CarrierOne().RateInput()->Set(1.0);
	channel.CarrierOne().Envelope().SustainInput()->Set(0.7);
	channel.CarrierOne().Envelope().DecayInput()->Set(0.05);
	channel.CarrierOne().Envelope().AttackInput()->Set(5e-4);
	channel.CarrierOne().Envelope().ReleaseInput()->Set(0.01);

	channel.ModulatorTwo().GainInput()->Set(0.8);
	channel.ModulatorTwo().RateInput()->Set(1.0);
	channel.ModulatorTwo().Envelope().SustainInput()->Set(0.7);
	channel.ModulatorTwo().Envelope().DecayInput()->Set(0.1);
	channel.ModulatorTwo().Envelope().AttackInput()->Set(5e-4);
	channel.ModulatorTwo().Envelope().ReleaseInput()->Set(0.01);

	channel.CarrierTwo().GainInput()->Set(0.8);
	channel.CarrierTwo().RateInput()->Set(1.0);
	channel.CarrierTwo().Envelope().SustainInput()->Set(0.7);
	channel.CarrierTwo().Envelope().DecayInput()->Set(0.1);
	channel.CarrierTwo().Envelope().AttackInput()->Set(5e-4);
	channel.CarrierTwo().Envelope().ReleaseInput()->Set(0.01);
}

void ConfigureSquare(PsgToneChannel& channel, Voice& voice, double detune)
{
	channel.GateInput()->Connect(voice.GateOutput());
	channel.PitchInput()->Connect(voice.PitchOutput());
	channel.Envelope().SustainInput()->Set(0.5);
	channel.Envelope().DecayInput()->Set(1.0);
	channel.DetuneInput()->Set(detune);
	channel.VolumeInput()->Set(0.5);
}

void GreenHill()
{
	static const double fs = 44100;
	static const double ts = 1 / fs;
	static const double duration = 55;

	MidiFilePlayer midiFilePlayer("GreenHillMegadrive.mid", ts, 1.0);
	auto drumTrack = midiFilePlayer.CreateDrumTrack(10);
	auto brassTrack = midiFilePlayer.CreateTrack(1, 3);
	auto bassTrack = midiFilePlayer.CreateTrack(4);
	auto epTrack = midiFilePlayer.CreateTrack(5);
	auto squareTrack = midiFilePlayer.CreateTrack(2, 2);

	Megadrive megadrive(ts, 8, 4);
	megadrive.GainInput()->Set(0.3);
	ControlSignalGenerator pitchEnvelopeControl(ts, { Node(0, 2.0), Node(14, 0.0) });
	
	ConfigureDrums(megadrive.Dac(), drumTrack);

	ConfigureBrass(megadrive.FmChannel(0), brassTrack, 0, 0);
	ConfigureBrass(megadrive.FmChannel(1), brassTrack, 1, 0);
	ConfigureBrass(megadrive.FmChannel(2), brassTrack, 2, 0);
	megadrive.FmChannel(0).PitchEnvelope().GainInput()->Connect(pitchEnvelopeControl.Output());
	megadrive.FmChannel(1).PitchEnvelope().GainInput()->Connect(pitchEnvelopeControl.Output());
	megadrive.FmChannel(2).PitchEnvelope().GainInput()->Connect(pitchEnvelopeControl.Output());

	ConfigureBass(megadrive.FmChannel(3), bassTrack);

	Gain panGain;
	Sum panOffset(2);
	panGain.GetGainInput()->Set(2);
	panOffset.GetInputPort(0)->Connect(panGain.GetOutput());
	panOffset.GetInputPort(1)->Set(-1);
	ConfigureEP(megadrive.FmChannel(4), epTrack, panGain.GetInput(), panOffset.Output());

	ConfigureSquare(megadrive.Psg().ChannelOne(), squareTrack.GetVoice(0), 0);
	ConfigureSquare(megadrive.Psg().ChannelTwo(), squareTrack.GetVoice(1), 0);
	
	WaveWriter waveWriter("GreenHillMegadrive.wav");

	waveWriter.LeftInput()->Connect(megadrive.LeftOutput());
	waveWriter.RightInput()->Connect(megadrive.RightOutput());

	ModuleRunner runner(&waveWriter);

	runner.Run(static_cast<int>(duration * fs));

	waveWriter.Close();
}
