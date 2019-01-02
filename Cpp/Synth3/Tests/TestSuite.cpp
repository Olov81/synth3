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
	bool success = true;

	for (std::vector<TestFunction>::iterator iter = _testFunctions.begin(); iter != _testFunctions.end(); ++iter)
	{
		success &= (*iter)();
	}

	return success;
}

void TestSuite::AddTest(TestFunction test)
{
	_testFunctions.push_back(test);
}

TestSuite* TestSuite::_pInstance;