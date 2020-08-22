#include "VoiceManager.h"
#include "Assert.h"
#include "SignalSink.h"
#include "Framework/ModuleRunner.h"

TEST(VoiceSplitter_should_write_output_to_the_allocated_voice)
{
	VoiceManager sut(1);
	ArraySink outputs;	
	auto& voice = sut.GetVoice(0);
	outputs.GetInput("Pitch")->Connect(voice.PitchOutput());
	outputs.GetInput("Gate")->Connect(voice.GateOutput());

	sut.NoteOn(100, 127);
	ModuleRunner runner(&outputs);
	runner.Run(1);

	ASSERT_EQUAL(31, outputs.GetSample("Pitch", 0));
	ASSERT_EQUAL(1, outputs.GetSample("Gate", 0));
}

TEST(VoiceSplitter_should_write_output_to_free_voice)
{
	VoiceManager sut(2);
	ArraySink outputs;
	auto& voice = sut.GetVoice(1);
	outputs.GetInput("Pitch")->Connect(voice.PitchOutput());
	outputs.GetInput("Gate")->Connect(voice.GateOutput());

	sut.NoteOn(100, 127);
	sut.NoteOn(99, 254);
	ModuleRunner runner(&outputs);
	runner.Run(1);
	
	ASSERT_EQUAL(30, outputs.GetSample("Pitch", 0));
	ASSERT_EQUAL(2, outputs.GetSample("Gate", 0));
}

TEST(VoiceSplitter_should_steel_voice_if_there_are_none_free)
{
	VoiceManager sut(1);
	ArraySink outputs;
	auto& voice = sut.GetVoice(0);
	outputs.GetInput("Pitch")->Connect(voice.PitchOutput());
	outputs.GetInput("Gate")->Connect(voice.GateOutput());

	sut.NoteOn(100, 127);
	sut.NoteOn(99, 254);
	ModuleRunner runner(&outputs);
	runner.Run(1);

	ASSERT_EQUAL(30, outputs.GetSample("Pitch", 0));
	ASSERT_EQUAL(2, outputs.GetSample("Gate", 0));
}

TEST(VoiceSplitter_should_use_freed_voice)
{
	VoiceManager sut(2);
	ArraySink outputs;
	auto& voice = sut.GetVoice(1);
	outputs.GetInput("Pitch")->Connect(voice.PitchOutput());
	outputs.GetInput("Gate")->Connect(voice.GateOutput());

	sut.NoteOn(100, 127);
	sut.NoteOn(99, 254);
	sut.NoteOff(99);
	sut.NoteOn(98, 127);
	ModuleRunner runner(&outputs);
	runner.Run(1);

	ASSERT_EQUAL(29, outputs.GetSample("Pitch", 0));
	ASSERT_EQUAL(1, outputs.GetSample("Gate", 0));
}