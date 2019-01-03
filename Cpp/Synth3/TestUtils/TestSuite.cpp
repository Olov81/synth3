#include "TestSuite.h"
#include <iostream>

TestSuite * TestSuite::Instance()
{
	if (_pInstance == 0)
	{
		_pInstance = new TestSuite();
	}

	return _pInstance;
}

bool TestSuite::RunTests()
{
	try
	{
		for (std::vector<Test>::iterator iter = _testFunctions.begin(); iter != _testFunctions.end(); ++iter)
		{
			std::cout << "Running test " << iter->_name << "... ";
			iter->_function();
			std::cout << "passed!" << std::endl;
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
	Test test(testFunction, testName);

	_testFunctions.push_back(test);
}

TestSuite::TestSuite()
{
}

TestSuite* TestSuite::_pInstance;