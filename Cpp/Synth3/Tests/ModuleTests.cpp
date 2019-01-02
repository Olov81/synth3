#include "ModuleTests.h"
#include "../Module.h"

class TestModule : public Module
{
public:

	IInputPort* GetInputOne()
	{
		return _pInputOne;
	}

	IInputPort* GetInputTwo()
	{
		return _pInputTwo;
	}

	IOutputPort* GetOutputOne()
	{
		return _pOutputOne;
	}

	IOutputPort* GetOutputTwo()
	{
		return _pOutputTwo;
	}

	const std::string& GetName() const
	{
		return _name;
	}

	TestModule(std::string name)
		:_name(name)
	{
		_pInputOne = CreateInputPort();
		_pInputTwo = CreateInputPort();
		_pOutputOne = CreateOutputPort();
		_pOutputTwo = CreateOutputPort();
	}

	// Inherited via Module
	virtual void Update() override
	{
	}

private:

	IInputPort* _pInputOne;
	IInputPort* _pInputTwo;
	IOutputPort* _pOutputOne;
	IOutputPort* _pOutputTwo;
	std::string _name;
};

void ModuleTests()
{
	TestModule moduleOne("One");
	TestModule moduleTwo("Two");
	TestModule moduleThree("Three");
	TestModule moduleFour("Four");

	moduleTwo.GetInputOne()->Connect(moduleOne.GetOutputOne());
	moduleThree.GetInputOne()->Connect(moduleOne.GetOutputTwo());

	moduleTwo.GetInputTwo()->Connect(moduleThree.GetOutputTwo());

	moduleFour.GetInputOne()->Connect(moduleTwo.GetOutputOne());
	moduleFour.GetInputTwo()->Connect(moduleThree.GetOutputOne());

	std::vector<IModule*> modules = GetDependenciesInUpdateOrder(&moduleFour);
}
