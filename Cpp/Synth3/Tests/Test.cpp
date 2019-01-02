#include "ModuleRunnerTests.h"
#include "InterpolatorTests.h"
#include "TwoPoleLowpassFilterTests.h"
#include "SampleBufferTests.h"

int main()
{
	ModuleRunnerTests();
	InterpolatorTests();
	TwoPoleLowpassFilterTests();
	SampleBufferTests();
}