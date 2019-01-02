#include "SampleBufferTests.h"
#include "../SampleBuffer.h"
#include "Assert.h"

void TestWithoutLoop()
{
	double samples[] = { 1, 2 };

	SampleBuffer buffer(samples, 2);

	buffer.Update();
	AssertEqual(1.0, buffer.GetOutput()->Read());
	buffer.Update();
	AssertEqual(2.0, buffer.GetOutput()->Read());
	buffer.Update();
	AssertEqual(0.0, buffer.GetOutput()->Read());
}

void TestWithLoop()
{
	double samples[] = { 10, 20, 30, 40 };

	SampleBuffer buffer(samples, 4);
	buffer.SetLoopEnabled(true);
	buffer.SetLoopInterval(1, 2);

	buffer.Update();
	AssertEqual(10, buffer.GetOutput()->Read());
	buffer.Update();
	AssertEqual(20, buffer.GetOutput()->Read());
	buffer.Update();
	AssertEqual(30, buffer.GetOutput()->Read());
	buffer.Update();
	AssertEqual(20, buffer.GetOutput()->Read());
	buffer.Update();
	AssertEqual(30, buffer.GetOutput()->Read());
}

void SampleBufferTests()
{
	TestWithoutLoop();
	TestWithLoop();
}


