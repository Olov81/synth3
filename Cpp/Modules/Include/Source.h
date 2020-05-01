#pragma once
#include "Framework/Module.h"

class Source : public Module
{
public:

	IOutputPort* Output() const;

protected:

	Source();

	void Write(const double& value) const;

private:

	IOutputPort* _pOutput;
};