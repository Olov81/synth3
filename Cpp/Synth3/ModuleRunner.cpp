#include "ModuleRunner.h"
#include "IModule.h"
#include "IOutputPort.h"
#include "IInputPort.h"

ModuleRunner::ModuleRunner(IModule * pModule)
{
	_modules = GetDependenciesInUpdateOrder(pModule);
}

void ModuleRunner::Run(unsigned int samples)
{
	for (unsigned int n = 0; n < samples; ++n)
	{
		UpdateModules();
	}
}

ModuleRunner::ModuleCollection ModuleRunner::GetDependenciesInUpdateOrder(IModule * pModule)
{
	ModuleCollection dependencies;

	for (unsigned int i = 0; i < pModule->GetNumberOfInputs(); ++i)
	{
		const IInputPort* pInput = pModule->GetInputPort(i);

		const IOutputPort* pConnection = pInput->GetConnection();

		if (pConnection != 0)
		{
			IModule* pDependency = pConnection->GetOwnerModule();

			if (std::find(dependencies.begin(), dependencies.end(), pDependency) == dependencies.end())
			{
				ModuleCollection subDependencies = GetDependenciesInUpdateOrder(pDependency);

				for (ModuleCollection::iterator iter = subDependencies.begin(); iter != subDependencies.end(); ++iter)
				{
					if (std::find(dependencies.begin(), dependencies.end(), *iter) == dependencies.end())
					{
						dependencies.push_back(*iter);
					}
				}
			}
		}
	}

	dependencies.push_back(pModule);

	return dependencies;
}

void ModuleRunner::UpdateModules()
{
	for (ModuleCollection::iterator iter = _modules.begin(); iter != _modules.end(); ++iter)
	{
		(*iter)->Update();
	}
}

