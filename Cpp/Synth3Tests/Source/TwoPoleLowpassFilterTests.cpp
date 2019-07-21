#include "TwoPoleLowpassFilter.h"
#include "Assert.h"

TEST(TwoPoleLowpassFilterTests)
{
	TwoPoleLowpassFilter filter;

	auto y1 = filter.Update(1.0);
	auto y2 = filter.Update(1.0);
	auto y3 = filter.Update(1.0);

	ASSERT_GREATER(0, y1);
	ASSERT_GREATER(y1, y2);
	ASSERT_GREATER(y2, y3);
}
