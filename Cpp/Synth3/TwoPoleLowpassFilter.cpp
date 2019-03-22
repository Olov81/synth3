#define _USE_MATH_DEFINES

#include "TwoPoleLowpassFilter.h"
#include <math.h>

TwoPoleLowpassFilter::TwoPoleLowpassFilter()
	:_cutoff(0.5)
	,_q(1.0)
{
	UpdateCoefficients();
}

void TwoPoleLowpassFilter::SetCutoffFrequency(double cutoff)
{
	_cutoff = cutoff;
	UpdateCoefficients();
}

void TwoPoleLowpassFilter::SetQ(double q)
{
	_q = q;
	UpdateCoefficients();
}

void TwoPoleLowpassFilter::UpdateFilterCoefficients(double A[BufferSize], double B[BufferSize])
{
	double wc = 2 * M_PI*_cutoff;
	double wc2 = wc * wc;

	A[0] = 1 + 4 * _q / wc + 4 / wc2;
	A[1] = 2 - 8 / wc2;
	A[2] = 1 - 4 * _q / wc + 4 / wc2;

	B[0] = 1;
	B[1] = 2;
	B[2] = 1;
}
