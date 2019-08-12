#include "ContinuousFilterFactory.h"

FilterMode::FilterMode(double lambda, double c)
: _lambda(lambda)
, _c(c)
{
}

double FilterMode::Lambda() const
{
	return _lambda;
}

double FilterMode::c() const
{
	return _c;
}

ContinuousFilterParameters::ContinuousFilterParameters(size_t order)
: _order(order)
{
}

size_t ContinuousFilterParameters::Order()
{
	return _order;
}

ContinuousFilterParameters ContinuousFilterFactory::CreateRealPoleFilter(size_t order, double cutoffFrequency)
{
}
