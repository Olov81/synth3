#include "SampleBufferTests.h"
#include "../SampleBuffer.h"
#include "Assert.h"
#include "SignalSink.h"
#include "../ModuleRunner.h"


void TestWithoutLoop()
{
	double samples[] = { 1, 2 };

	SampleBuffer buffer(samples, 2);
	SignalSink sink;

	sink.GetInput()->Connect(buffer.GetOutput());

	ModuleRunner runner(&sink);

	runner.Run(4);

	AssertEqual(1.0, sink.GetSample(0));
	AssertEqual(2.0, sink.GetSample(1));
	AssertEqual(0.0, sink.GetSample(2));
}

void TestWithLoop()
{
	double samples[] = { 10, 20, 30, 40 };

	SampleBuffer buffer(samples, 4);
	buffer.SetLoopEnabled(true);
	buffer.SetLoopInterval(1, 2);
	SignalSink sink;

	sink.GetInput()->Connect(buffer.GetOutput());

	ModuleRunner runner(&sink);

	runner.Run(5);

	AssertEqual(10, sink.GetSample(0));
	AssertEqual(20, sink.GetSample(1));
	AssertEqual(30, sink.GetSample(2));
	AssertEqual(20, sink.GetSample(3));
	AssertEqual(30, sink.GetSample(4));
}

void SampleBufferTests()
{
	TestWithoutLoop();
	TestWithLoop();
}


