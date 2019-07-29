#include "TestSuite.h"

int main()
{
	return TestSuite::Instance()->RunTests() ? 0 : -1;
}