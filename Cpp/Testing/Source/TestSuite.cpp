#include "TestSuite.h"
#include <iostream>

TestSuite * TestSuite::Instance()
{
	if (_pInstance == nullptr)
	{
		_pInstance = new TestSuite();
	}

	return _pInstance;
}

bool TestSuite::RunTests()
{
	try
	{
		for (auto& testFunction : _testFunctions)
		{
			if(testFunction._ignore)
			{
				std::cout << "Ignoring test " << testFunction._name << std::endl;
			}
			else
			{
				std::cout << "Running test " << testFunction._name << "... ";
				testFunction._function();
				std::cout << "passed!" << std::endl;
			}
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void TestSuite::AddTest(TestFunction testFunction, const char* testName)
{
	const Test test(testFunction, testName, false);

	_testFunctions.push_back(test);
}

void TestSuite::IgnoreTest(const char* testName)
{
	const Test test([]() {}, testName, true);
	
	_testFunctions.push_back(test);
}

TestSuite::TestSuite() = default;

TestSuite* TestSuite::_pInstance;