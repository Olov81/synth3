#pragma once

class ISampleProvider
{
public:
	virtual ~ISampleProvider() = default;

	virtual double GetNextSample() = 0;
};
