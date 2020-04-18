#pragma once
#include "Framework/Module.h"

class SignalSplitter : public Module
{
public:

	SignalSplitter(size_t numberOfOutputs);

	void Update() override;

	IInputPort* Input() const;

	IOutputPort* GetOutput(size_t n) const;

private:

	IInputPort* _pInput;

	std::vector<IOutputPort*> _outputs;
};
