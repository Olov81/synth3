#pragma once
#include "LinearFilter.h"

class TwoPoleLowpassFilter : public LinearFilter<2>
{
public:

	TwoPoleLowpassFilter();

	void SetCutoffFrequency(double cutoff);

	void SetQ(double q);

private:

	virtual void UpdateFilterCoefficients(double A[BufferSize], double B[BufferSize]);

	double _cutoff;

	double _q;
};