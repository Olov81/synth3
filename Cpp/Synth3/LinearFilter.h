#pragma once
#include <memory>
#include "Framework/Module.h"
#include "IFilter.h"

template<size_t Order>
class LinearFilter : public IFilter
{
protected:

	static const size_t BufferSize = Order + 1;

	void UpdateCoefficients()
	{
		UpdateFilterCoefficients(_A, _B);
	}

public:

	LinearFilter()
		:_index(0)
	{
		ResetBuffer(_pInputState);
		ResetBuffer(_pOutputState);
	}

	double Update(double x)
	{
		_pInputState[_index] = x;

		double y = 0;

		for (unsigned int k = 0; k < BufferSize; ++k)
		{
			unsigned int delayIndex = (_index + k + 1) % BufferSize;
			unsigned int coefficientIndex = BufferSize - k - 1;

			y = y + _B[coefficientIndex] * _pInputState[delayIndex];

			if (delayIndex != _index)
			{
				y = y - _A[coefficientIndex] * _pOutputState[delayIndex];
			}
		}

		y = y / _A[0];

		_pOutputState[_index] = y;

		_index = (_index + 1) % BufferSize;

		return y;
	}

private:

	virtual void UpdateFilterCoefficients(double A[BufferSize], double B[BufferSize]) = 0;

	void ResetBuffer(double* pBuffer)
	{
		memset(pBuffer, 0, BufferSize * sizeof(double));
	}

	double _pInputState[BufferSize];
	double _pOutputState[BufferSize];
	double _A[BufferSize];
	double _B[BufferSize];
	unsigned int _index;
};