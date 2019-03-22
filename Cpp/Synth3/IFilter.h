#pragma once

class IFilter
{
public:
	virtual ~IFilter() = default;

	virtual void SetCutoffFrequency(double frequency) = 0;

	virtual double Update(double input) = 0;
};

