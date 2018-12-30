#include "Module.h"
#include <algorithm>

Module::Module()
{
}

IInputPort* Module::CreateInputPort()
{
	InputPort* pPort = new InputPort();

	_inputPorts.push_back(pPort);

	return pPort;
}

IOutputPort* Module::CreateOutputPort()
{
	OutputPort* pPort = new OutputPort(this);

	_outputPorts.push_back(pPort);

	return pPort;
}

unsigned int Module::GetNumberOfInputs() const
{
	return _inputPorts.size();
}

const IInputPort* Module::GetInputPort(unsigned int index) const
{
	return _inputPorts[index];
}

std::vector<IModule*> GetDependenciesInUpdateOrder(IModule * pModule)
{
	std::vector<IModule*> dependencies;

	for (unsigned int i = 0; i < pModule->GetNumberOfInputs(); ++i)
	{
		const IInputPort* pInput = pModule->GetInputPort(i);

		const IOutputPort* pConnection = pInput->GetConnection();

		if (pConnection != 0)
		{
			IModule* pDependency = pConnection->GetOwnerModule();

			if (std::find(dependencies.begin(), dependencies.end(), pDependency) == dependencies.end())
			{
				std::vector<IModule*> subDependencies = GetDependenciesInUpdateOrder(pDependency);

				for (std::vector<IModule*>::iterator iter = subDependencies.begin(); iter != subDependencies.end(); ++iter)
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
