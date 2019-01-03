#pragma once

#include <vector>

class TestSuite
{
public:

	static TestSuite* Instance();

	typedef void(*TestFunction)();

	bool RunTests();

	void AddTest(TestFunction test);

private:

	std::vector<TestFunction> _testFunctions;

	static TestSuite* _pInstance;
};