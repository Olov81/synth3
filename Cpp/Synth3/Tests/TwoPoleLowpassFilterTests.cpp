#include "TwoPoleLowpassFilterTests.h"
#include "../TwoPoleLowpassFilter.h"
#include "Assert.h"

void TwoPoleLowpassFilterTests()
{
	TwoPoleLowpassFilter filter;

	double y1 = filter.Update(1.0);
	double y2 = filter.Update(1.0);
	double y3 = filter.Update(1.0);

	AssertGreater(0, y1);
	AssertGreater(y1, y2);
	AssertGreater(y2, y3);
}
