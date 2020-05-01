#include "EnvelopeGenerator.h"
#include "Assert.h"
#include "SignalSink.h"
#include "Framework/ModuleRunner.h"
#include "SignalSource.h"

TEST(EnvelopeGenerator_full_cycle)
{
	EnvelopeGenerator generator(1.0);
	SignalSink generatorOutput;

	SignalSource gate({ 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0 });
	generator.AttackInput()->Set(2.0);
	generator.DecayInput()->Set(4.0);
	generator.SustainInput()->Set(0.4);
	generator.ReleaseInput()->Set(5.0);

	generator.GateInput()->Connect(gate.GetOutput());
	generatorOutput.GetInput()->Connect(generator.Output());

	ModuleRunner runner(&generatorOutput);

	runner.Run(10);

	ASSERT_EQUAL(0.0, generatorOutput.GetSample(0));
	ASSERT_EQUAL(0.5, generatorOutput.GetSample(1));
	ASSERT_EQUAL(1.0, generatorOutput.GetSample(2));
	ASSERT_EQUAL(0.75, generatorOutput.GetSample(3));
	ASSERT_EQUAL(0.5, generatorOutput.GetSample(4));
	ASSERT_EQUAL(0.4, generatorOutput.GetSample(5));
	ASSERT_EQUAL(0.4, generatorOutput.GetSample(6));
	ASSERT_EQUAL(0.2, generatorOutput.GetSample(7));
	ASSERT_EQUAL(0.0, generatorOutput.GetSample(8));
	ASSERT_EQUAL(0.0, generatorOutput.GetSample(9));
}

TEST(EnvelopeGenerator_release_during_attack_phase)
{
	EnvelopeGenerator generator(1.0);
	SignalSink generatorOutput;

	SignalSource gate({ 1.0, 0.0, 0.0 });
	generator.AttackInput()->Set(2.0);
	generator.ReleaseInput()->Set(5.0);

	generator.GateInput()->Connect(gate.GetOutput());
	generatorOutput.GetInput()->Connect(generator.Output());

	ModuleRunner runner(&generatorOutput);

	runner.Run(4);

	ASSERT_CLOSE(0.5, generatorOutput.GetSample(0), 1e-3);
	ASSERT_CLOSE(0.3, generatorOutput.GetSample(1), 1e-3);
	ASSERT_CLOSE(0.1, generatorOutput.GetSample(2), 1e-3);
	ASSERT_CLOSE(0.0, generatorOutput.GetSample(3), 1e-3);
}

TEST(EnvelopeGenerator_release_during_decay_phase)
{
	EnvelopeGenerator generator(1.0);
	SignalSink generatorOutput;

	SignalSource gate({ 1.0, 1.0, 0.0, 0.0, 0.0 });
	generator.AttackInput()->Set(1.0);
	generator.DecayInput()->Set(2.0);
	generator.ReleaseInput()->Set(5.0);

	generator.GateInput()->Connect(gate.GetOutput());
	generatorOutput.GetInput()->Connect(generator.Output());

	ModuleRunner runner(&generatorOutput);

	runner.Run(5);

	ASSERT_CLOSE(1.0, generatorOutput.GetSample(0), 1e-3);
	ASSERT_CLOSE(0.5, generatorOutput.GetSample(1), 1e-3);
	ASSERT_CLOSE(0.3, generatorOutput.GetSample(2), 1e-3);
	ASSERT_CLOSE(0.1, generatorOutput.GetSample(3), 1e-3);
	ASSERT_CLOSE(0.0, generatorOutput.GetSample(4), 1e-3);
}

TEST(EnvelopeGenerator_retrigger_during_release_phase)
{
	EnvelopeGenerator generator(1.0);
	SignalSink generatorOutput;

	SignalSource gate({ 1.0, 0.0, 1.0, 1.0 });
	generator.AttackInput()->Set(2.0);
	generator.ReleaseInput()->Set(5.0);

	generator.GateInput()->Connect(gate.GetOutput());
	generatorOutput.GetInput()->Connect(generator.Output());

	ModuleRunner runner(&generatorOutput);

	runner.Run(4);

	ASSERT_CLOSE(0.5, generatorOutput.GetSample(0), 1e-3);
	ASSERT_CLOSE(0.3, generatorOutput.GetSample(1), 1e-3);
	ASSERT_CLOSE(0.8, generatorOutput.GetSample(2), 1e-3);
	ASSERT_CLOSE(1.0, generatorOutput.GetSample(3), 1e-3);
}