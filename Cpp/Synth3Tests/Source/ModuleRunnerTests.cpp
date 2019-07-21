#include "Framework/Module.h"
#include "Framework/ModuleRunner.h"
#include "Assert.h"
#include <string>

class TestModule : public Module
{
public:

	IInputPort* GetInputOne() const
	{
		return _pInputOne;
	}

	IInputPort* GetInputTwo() const
	{
		return _pInputTwo;
	}

	IOutputPort* GetOutputOne() const
	{
		return _pOutputOne;
	}

	IOutputPort* GetOutputTwo() const
	{
		return _pOutputTwo;
	}

	TestModule(std::vector<IModule*>& updatedModules)
		:_updateModules(updatedModules)
	{
		_pInputOne = CreateInputPort();
		_pInputTwo = CreateInputPort();
		_pOutputOne = CreateOutputPort();
		_pOutputTwo = CreateOutputPort();
	}

	// Inherited via Module
	void Update() override
	{
		_updateModules.push_back(this);
	}

private:

	IInputPort* _pInputOne;
	IInputPort* _pInputTwo;
	IOutputPort* _pOutputOne;
	IOutputPort* _pOutputTwo;
	std::vector<IModule*>& _updateModules;
};

TEST(ModuleRunnerTests)
{
	std::vector<IModule*> updatedModules;

	TestModule moduleOne(updatedModules);
	TestModule moduleTwo(updatedModules);
	TestModule moduleThree(updatedModules);
	TestModule moduleFour(updatedModules);

	moduleTwo.GetInputOne()->Connect(moduleOne.GetOutputOne());
	moduleThree.GetInputOne()->Connect(moduleOne.GetOutputTwo());

	moduleTwo.GetInputTwo()->Connect(moduleThree.GetOutputTwo());

	moduleFour.GetInputOne()->Connect(moduleTwo.GetOutputOne());
	moduleFour.GetInputTwo()->Connect(moduleThree.GetOutputOne());

	ModuleRunner runner(&moduleFour);

	runner.Run(2);

	ASSERT_EQUAL(&moduleOne, updatedModules[0]);
	ASSERT_EQUAL(&moduleThree, updatedModules[1]);
	ASSERT_EQUAL(&moduleTwo, updatedModules[2]);
	ASSERT_EQUAL(&moduleFour, updatedModules[3]);
	ASSERT_EQUAL(&moduleOne, updatedModules[4]);
	ASSERT_EQUAL(&moduleThree, updatedModules[5]);
	ASSERT_EQUAL(&moduleTwo, updatedModules[6]);
	ASSERT_EQUAL(&moduleFour, updatedModules[7]);
}
