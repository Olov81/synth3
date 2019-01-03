#include "../SamplePlayer.h"
#include "../TestUtils/Assert.h"
#include "../TestUtils/SignalSource.h"
#include "../TestUtils/SignalSink.h"
#include "Framework/ModuleRunner.h"

TEST(SamplePlayerTests)
{
	const double sampleBuffer[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	SamplePlayer player(sampleBuffer, sizeof(sampleBuffer) / sizeof(double));
	SignalSource decimationSource({ 2.0, 2.0, 0.5, 0.5 });
	SignalSink signalSink;

	player.GetDecimationInput()->Connect(decimationSource.GetOutput());
	signalSink.GetInput()->Connect(player.GetOutput());

	ModuleRunner runner(&signalSink);

	runner.Run(4);

	ASSERT_GREATER(1.0, signalSink.GetSample(0));
	ASSERT_GREATER(3.0, signalSink.GetSample(1));
	ASSERT_LESS(5.0, signalSink.GetSample(2));
	ASSERT_LESS(5.0, signalSink.GetSample(3));
}
