#pragma once
#include <vector>

class IModule;

class ModuleRunner
{
public:

	ModuleRunner(IModule* pModule);

	void Run(unsigned int samples);

private:

	typedef std::vector<IModule*> ModuleCollection;

	ModuleCollection _modules;

	ModuleCollection GetDependenciesInUpdateOrder(IModule * pModule);

	void UpdateModules();
};
