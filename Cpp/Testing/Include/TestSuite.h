#pragma once

#include <vector>

class TestSuite
{
public:

	static TestSuite* Instance();

	typedef void(*TestFunction)();

	bool RunTests();

	void AddTest(TestFunction testFunction, const char* testName);

	void IgnoreTest(const char* testName);
	
private:

	TestSuite();

	struct Test
	{
		Test(TestFunction function, const char* name, bool ignore)
			:_function(function)
			,_name(name)
			,_ignore(ignore)	

		{
		}

		TestFunction _function;
		const char* _name;
		bool _ignore;
	};

	std::vector<Test> _testFunctions;
	static TestSuite* _pInstance;
};