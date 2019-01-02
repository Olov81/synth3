#include "Assert.h"

void AssertGreater(double limit, double actual)
{
	if (actual <= limit)
	{
		std::cout << "Expected value to be greater than " << limit << " but was " << actual << std::endl;;
	}
}

void AssertInRange(double min, double max, double actual)
{
	if (!(min <= actual && actual <= max))
	{
		std::cout << "Expected value to in range [" << min << ", " << max << "] but was " << actual << std::endl;;
	}
}
