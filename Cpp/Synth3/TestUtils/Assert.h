#pragma once
#include <iostream>
#include "TestSuite.h"

#define TEST(name)\
static void name();\
static bool init##name()\
{\
	TestSuite::Instance()->AddTest(name, #name);\
	return true;\
}\
static bool name##initialized = init##name();\
void name()

#define ASSERT_EQUAL(expected, actual)\
AssertEqual(expected, actual, __LINE__, __FILE__, #actual);

#define ASSERT_GREATER(limit, actual)\
AssertGreater(limit, actual, __LINE__, __FILE__, #actual);

#define ASSERT_LESS(limit, actual)\
AssertLess(limit, actual, __LINE__, __FILE__, #actual);

template<class TExpected, class TActual>
void AssertEqual(TExpected expected, TActual actual, long line, const char* file, const char* expectedName)
{
	if (!(expected == actual))
	{
		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be " << expected << " but was " << actual << std::endl;
		throw std::exception("Test failed");
	}
}

template<class TLimit, class TActual>
void AssertGreater(TLimit limit, TActual actual, long line, const char* file, const char* expectedName)
{
	if (!(actual > limit))
	{
		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be greater than " << limit << " but was " << actual << std::endl;
		throw std::exception("Test failed");
	}
}

template<class TLimit, class TActual>
void AssertLess(TLimit limit, TActual actual, long line, const char* file, const char* expectedName)
{
	if (!(actual < limit))
	{
		std::cout << std::endl << file << "(" << line << "): Expected " << expectedName << " to be less than " << limit << " but was " << actual << std::endl;
		throw std::exception("Test failed");
	}
}