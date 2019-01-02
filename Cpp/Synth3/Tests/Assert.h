#pragma once
#include <iostream>
#include "TestSuite.h"

#define TEST(name)\
static void name##impl();\
bool name()\
{\
	try\
		{ name##impl(); }\
	catch(...)\
		{ return false; }\
	return true;\
}\
static bool init##name()\
{\
	TestSuite::Instance()->AddTest(name);\
	return true;\
}\
static bool name##init = init##name();\
void name##impl()

#define ASSERT_EQUAL(expected, actual)\
AssertEqual(expected, actual, __LINE__, __FILE__, #actual);

template<class TExpected, class TActual>
void AssertEqual(TExpected expected, TActual actual, long line, const char* file, const char* expectedName)
{
	if (!(expected == actual))
	{
		std::cout << file << "(" << line << "): Expected " << expectedName << " to be " << expected << " but was " << actual << std::endl;
		throw std::exception("Test failed");
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