#include "TwoPoleLowpassFilter.h"
#include "TestUtils/Assert.h"

TEST(TwoPoleLowpassFilterTests)
{
	TwoPoleLowpassFilter filter;

	double y1 = filter.Update(1.0);
	double y2 = filter.Update(1.0);
	double y3 = filter.Update(1.0);

	ASSERT_GREATER(0, y1);
	ASSERT_GREATER(y1, y2);
	ASSERT_GREATER(y2, y3);
}
