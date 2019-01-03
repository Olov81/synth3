#include "TestSuite.h"

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
		for (std::vector<TestFunction>::iterator iter = _testFunctions.begin(); iter != _testFunctions.end(); ++iter)
		{
			(*iter)();
		}
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void TestSuite::AddTest(TestFunction test)
{
	_testFunctions.push_back(test);
}

TestSuite* TestSuite::_pInstance;