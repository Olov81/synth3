#pragma once
#include <vector>

struct LinearFunction
{
	LinearFunction(double _k, double _m, double _omega)
		: k(_k)
		, m(_m)
		, omega(_omega)
	{
	}

	double k;
	double m;
	double omega;
};

class Waveforms
{
public:

	static std::vector<LinearFunction> Sawtooth()
	{
		return
		{
			LinearFunction(1, 0, 0),
			LinearFunction(0,0,1.0)
		};
	}

	static std::vector<LinearFunction> Square()
	{
		return
		{
			LinearFunction(0, 1, 0),
			LinearFunction(0, 0, 0.5),
			LinearFunction(0,0,1.0)
		};
	}

	static std::vector<LinearFunction> HalfPulse()
	{
		return
		{
			LinearFunction(0, 1, 0),
			LinearFunction(0, 0, 0.25),
			LinearFunction(0,0,1.0)
		};
	}

	static std::vector<LinearFunction> QuarterPulse()
	{
		return
		{
			LinearFunction(0, 1, 0),
			LinearFunction(0, 0, 0.125),
			LinearFunction(0,0,1.0)
		};
	}

	static std::vector<LinearFunction> Triangle()
	{
		return
		{
			LinearFunction(2, 0, 0),
			LinearFunction(-2, 2, 0.5),
			LinearFunction(0,0,1.0)
		};
	}
};
