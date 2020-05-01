#include "Source.h"

Source::Source()
{
	_pOutput = CreateOutputPort();
}

void Source::Write(const double& value) const
{
	_pOutput->Write(value);
}

IOutputPort* Source::Output() const
{
	return _pOutput;
}
