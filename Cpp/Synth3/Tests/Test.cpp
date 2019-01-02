#include "ModuleRunnerTests.h"
#include "InterpolatorTests.h"
#include "TwoPoleLowpassFilterTests.h"
#include "SampleBufferTests.h"

int main()
{
	bool passed = true;
	passed &= ModuleRunnerTests();
	InterpolatorTests();
	TwoPoleLowpassFilterTests();
	SampleBufferTests();

	return passed ? 0 : -1;
}