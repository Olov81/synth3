#pragma once
#include <vector>
#include <cmath>

struct WaveformPoint
{
public:

	WaveformPoint(double _omega, double _y)
		: omega(_omega)
		, y(_y)
	{
	}
	
	
	double omega;
	double y;
};

struct LinearFunction
{
	LinearFunction(WaveformPoint p1, WaveformPoint p2)
		: k((p2.y - p1.y) / (p2.omega - p1.omega))
		, m(p1.y - k * p1.omega)
		, omegaStart(p1.omega)
		, omega(p2.omega)
		, start(p1.y)
	{
	}
	
	LinearFunction(double _k, double _start, double _omega)
		: k(_k)
		, m(_start - _k*_omega)
		, omega(_omega)
		, start(_start)
	{
		
	}

	LinearFunction(double _k, double _m, double _omegaStart, double _omegaEnd)
		: k(_k)
		, m(_m)
		, omegaStart(_omegaStart)
		, omega(_omegaEnd)
	{

	}

	double k;
	double m;
	double omegaStart;
	double omega;
	double start;
};

inline bool AreClose(const double& v1, const double& v2)
{
	const auto precision = 1e-5;

	return std::abs(v1 - v2) < precision;
}

inline bool operator == (const LinearFunction& f1, const LinearFunction& f2)
{
	return AreClose(f1.k, f2.k) && AreClose(f1.m, f2.m) && AreClose(f1.omega, f2.omega);
}

class Waveforms
{
public:

	static std::vector<LinearFunction> Sawtooth()
	{
		return
		{
			LinearFunction(1, 0, 1.0),
			LinearFunction(1, 1, 2.0)
		};
	}

	static std::vector<LinearFunction> Square()
	{
		return
		{
			LinearFunction(0, 1, 0),
			LinearFunction(0, 0, 0.5),
			LinearFunction(0,1,1.0)
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
			LinearFunction(-2, 1, 0.5),
			LinearFunction(0,0,1.0)
		};
	}

	static std::vector<LinearFunction> CustomOne()
	{
		return
		{
			LinearFunction(-2.7, 1, 0),
			LinearFunction(0, 0, 0.5),
			LinearFunction(-2.7, 1, 1.0),
		};
	}
};
