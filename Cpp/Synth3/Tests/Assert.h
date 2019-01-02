#pragma once
#include <iostream>

#define ASSERT_EQUAL(expected, actual)\
AssertEqual(expected, actual, __LINE__, __FILE__, #actual);

template<class TExpected, class TActual>
void AssertEqual(TExpected expected, TActual actual, long line, const char* file, const char* expectedName)
{
	if (!(expected == actual))
	{
		std::cout << file << "(" << line << "): Expected " << expectedName << " to be " << expected << " but was " << actual << std::endl;
	}
}

template<class TExpected, class TActual>
void AssertEqual(TExpected expected, TActual actual)
{
	if (!(expected == actual))
	{
		std::cout << "Expected value to be " << expected << " but was " << actual << std::endl;
	}
}

void AssertGreater(double limit, double actual);

void AssertInRange(double min, double max, double actual);