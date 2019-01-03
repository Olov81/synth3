#include "SampleBufferModule.h"
#include "TestUtils/Assert.h"
#include "TestUtils/SignalSink.h"
#include "Framework/ModuleRunner.h"

namespace SampleBufferModuleTests
{

TEST(TestWithoutLoop)
{
	double samples[] = { 1, 2 };

	SampleBufferModule buffer(samples, 2);
	SignalSink sink;

	sink.GetInput()->Connect(buffer.GetOutput());

	ModuleRunner runner(&sink);

	runner.Run(4);

	ASSERT_EQUAL(1.0, sink.GetSample(0));
	ASSERT_EQUAL(2.0, sink.GetSample(1));
	ASSERT_EQUAL(0.0, sink.GetSample(2));
}

TEST(TestWithLoop)
{
	double samples[] = { 10, 20, 30, 40 };

	SampleBufferModule buffer(samples, 4);
	buffer.SetLoopEnabled(true);
	buffer.SetLoopInterval(1, 2);
	SignalSink sink;

	sink.GetInput()->Connect(buffer.GetOutput());

	ModuleRunner runner(&sink);

	runner.Run(5);

	ASSERT_EQUAL(10, sink.GetSample(0));
	ASSERT_EQUAL(20, sink.GetSample(1));
	ASSERT_EQUAL(30, sink.GetSample(2));
	ASSERT_EQUAL(20, sink.GetSample(3));
	ASSERT_EQUAL(30, sink.GetSample(4));
}

}

