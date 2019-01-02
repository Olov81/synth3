#include "ModuleTests.h"
#include "InterpolatorTests.h"
#include "TwoPoleLowpassFilterTests.h"
#include "SampleBufferTests.h"

int main()
{
	ModuleTests();
	InterpolatorTests();
	TwoPoleLowpassFilterTests();
	SampleBufferTests();
}