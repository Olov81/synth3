#pragma once

class ISampleProvider
{
public:
	virtual ~ISampleProvider() {};

	virtual double GetNextSample() = 0;
};
