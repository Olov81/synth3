#include "Assert.h"
#include "SyncFunctionProvider.h"
#include "LinearTableFunctionProvider.h"

std::ostream& operator<<(std::ostream& os, const LinearFunction& f)
{
	return os << "Omega = " << f.omega << ", k = " << f.k << ", m = " << f.m;
}

TEST(SyncFunctionProvider_should_return_decimated_function)
{
	LinearTableFunctionProvider provider(Waveforms::Square());
	SyncFunctionProvider sut(&provider);
	sut.SetFrequencyMultiplier(5.0 / 3);

	ASSERT_EQUAL(LinearFunction(0, 1, 0), sut.GetFunction(0));
	ASSERT_EQUAL(LinearFunction(0, 0, 0.3), sut.GetFunction(0.4));
	ASSERT_EQUAL(LinearFunction(0, 1, 0.6), sut.GetFunction(0.8));
	ASSERT_EQUAL(LinearFunction(0, 0, 0.9), sut.GetFunction(0.95));
}
