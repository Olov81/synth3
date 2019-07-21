#pragma once
#include "Source.h"

class Constant : public Source
{
public:

	Constant(double value);

	void Update() override;

private:

	double _value;
};
