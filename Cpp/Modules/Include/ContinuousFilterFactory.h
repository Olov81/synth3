#pragma once

class FilterMode
{
public:

	FilterMode(double lambda, double c);

	double Lambda() const;

	double c() const;

private:

	double _lambda;
	double _c;
};

class ContinuousFilterParameters
{
public:

	ContinuousFilterParameters(size_t order);

	size_t Order();

	const FilterMode& Mode(size_t index);

private:

	size_t _order;
};

class ContinuousFilterFactory
{
public:

	ContinuousFilterParameters CreateRealPoleFilter(size_t order, double cutoffFrequency);
};
