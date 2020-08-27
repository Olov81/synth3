#include "Assert.h"
#include "Sequencer.h"
#include "SignalSink.h"
#include "Framework/ModuleRunner.h"

TEST_IGNORE(GenerateFrequencies)
{
	auto ts = 0.6;

	Sequencer sequencer(
		ts,
		60,
		{
		SequencerEvent("A4", 1.0 / 4, 1.0 / 4, 1.0),
		SequencerEvent("Fb4", 1.0, 1.0 / 2, 0.7)
		});
	SignalSink frequencies;

	frequencies.GetInput()->Connect(sequencer.PitchOutput());

	ModuleRunner runner(&frequencies);

	runner.Run(4);

	ASSERT_EQUAL(0, frequencies.GetSample(0));
	ASSERT_EQUAL(0, frequencies.GetSample(1));
	ASSERT_CLOSE(-5, frequencies.GetSample(2), 5e-1);
	ASSERT_CLOSE(-5, frequencies.GetSample(3), 5e-1);
}

TEST(GenerateGate)
{
	auto ts = 0.6;

	Sequencer sequencer(
		ts,
		60,
		{
		SequencerEvent("A4", 1.0 / 4, 1.0 / 4, 1.0),
		SequencerEvent("A4", 1.0 / 4, 1.0 / 8, 0.7)
		});
	SignalSink gate;

	gate.GetInput()->Connect(sequencer.GateOutput());

	ModuleRunner runner(&gate);

	runner.Run(5);

	ASSERT_EQUAL(1.0, gate.GetSample(0));
	ASSERT_EQUAL(1.0, gate.GetSample(1));
	ASSERT_EQUAL(0.7, gate.GetSample(2));
	ASSERT_EQUAL(0.0, gate.GetSample(3));
	ASSERT_EQUAL(0.0, gate.GetSample(4));
}