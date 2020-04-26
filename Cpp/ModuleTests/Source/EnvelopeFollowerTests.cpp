#include "Assert.h"
#include "EnvelopeFollower.h"
#include "SignalSource.h"
#include "Framework/ModuleRunner.h"
#include "SignalSink.h"

TEST(EvenlopeFollower_should_convert_step_to_ramp)
{
	EnvelopeFollower sut(0.2);
	sut.TimeInput()->Set(0.5);

	SignalSource step({ 0, 1, 1, 1, 1, 1, 1 });
	SignalSink resultOutput;

	sut.GetInput()->Connect(step.GetOutput());
	resultOutput.GetInput()->Connect(sut.GetOutput());

	ModuleRunner runner(&resultOutput);

	runner.Run(6);

	ASSERT_CLOSE(0, resultOutput.GetSample(0), 1e-2);
	ASSERT_CLOSE(0.4, resultOutput.GetSample(1), 1e-2);
	ASSERT_CLOSE(0.64, resultOutput.GetSample(2), 1e-2);
	ASSERT_CLOSE(0.78, resultOutput.GetSample(3), 1e-2);
	ASSERT_CLOSE(0.87, resultOutput.GetSample(4), 1e-1);
	ASSERT_CLOSE(0.92, resultOutput.GetSample(5), 1e-2);
}
