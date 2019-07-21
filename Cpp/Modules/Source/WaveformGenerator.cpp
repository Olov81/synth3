#include "WaveformGenerator.h"
#include <complex>

static const double scale = 1000.0;
static const unsigned int order = 6;
static const double fs = 44100.0 / scale;
static const double ts = 1.0 / fs;

typedef std::complex<double> ComplexT;
static const ComplexT I = ComplexT(0, 1);

// 20 kHz
static const ComplexT lambda[order] =
{

	1.0e+02 * (-0.051531102528688 + 1.253107650494106 * I),
	1.0e+02 * (-0.051531102528688 - 1.253107650494106 * I),
	1.0e+02 * (-0.186107230804326 + 1.009403455191187 * I),
	1.0e+02 * (-0.186107230804326 - 1.009403455191187 * I),
	1.0e+02 * (-0.341121413723065 + 0.412660704960861 * I),
	1.0e+02 * (-0.341121413723065 - 0.412660704960861 * I)
};

static const ComplexT lambda2[order] =
{
	lambda[0] * lambda[0],
	lambda[1] * lambda[1],
	lambda[2] * lambda[2],
	lambda[3] * lambda[3],
	lambda[4] * lambda[4],
	lambda[5] * lambda[5]
};

static const ComplexT c1[order] =
{
	-0.849959499022492 + 0.262996584567710 * I,
	-0.849959499022492 - 0.262996584567710 * I,
	-0.431438602440959 + 0.493799212745242 * I,
	-0.431438602440959 - 0.493799212745242 * I,
	 0.273705895647727 + 0.371433865175301 * I,
	 0.273705895647727 - 0.371433865175301 * I
};

static const ComplexT c2[order] =
{
	-0.653464062005352 - 0.960363444341962 * I,
	-0.653464062005352 + 0.960363444341962 * I,
	 0.430418280636391 + 0.506874822688097 * I,
	 0.430418280636391 - 0.506874822688097 * I,
	 0.000324855944613 + 0.018554018695005 * I,
	 0.000324855944613 - 0.018554018695005 * I
};

static const ComplexT C_[order] =
{
	1.0e+02 * (-0.013843664160728 + 0.038955235452340 * I),
	1.0e+02 * (-0.013843664160728 - 0.038955235452340 * I),
	1.0e+02 * (-0.182700608492865 + 0.069012225024015 * I),
	1.0e+02 * (-0.182700608492865 - 0.069012225024015 * I),
	1.0e+02 * (-4.310989922168807 + 8.335007580485707 * I),
	1.0e+02 * (-4.310989922168807 - 8.335007580485707 * I)
};

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

LinearFunction waveform[] = {

	// Square wave
	LinearFunction(0, 1, 0),
	LinearFunction(0, 0, 0.5),
	LinearFunction(0,0,1.0)

	//Sawtooth
	//LinearFunction(1, 0, 0),
	//LinearFunction(0,0,1.0)

	// Triangle
	//LinearFunction(2, 0, 0),
	//LinearFunction(-2, 2, 0.5),
	//LinearFunction(0,0,1.0)
};

const LinearFunction& GetFunction(double t, double T)
{
	if (t > T)
	{
		return waveform[0];
	}

	const auto omega = t / T;

	const auto numberOfFunctions = sizeof(waveform) / sizeof(LinearFunction);

	for (size_t index = 0; index < numberOfFunctions - 1; ++index)
	{
		if (waveform[index].omega <= omega && omega < waveform[index + 1].omega)
		{
			return waveform[index];
		}
	}

	return waveform[0];
}

static const double a = -ts / 2;

static const ComplexT K[order] =
{
	exp(lambda[0] * a),
	exp(lambda[1] * a),
	exp(lambda[2] * a),
	exp(lambda[3] * a),
	exp(lambda[4] * a),
	exp(lambda[5] * a)
};

static const ComplexT K1[order] =
{
	lambda[0] * K[0],
	lambda[1] * K[1],
	lambda[2] * K[2],
	lambda[3] * K[3],
	lambda[4] * K[4],
	lambda[5] * K[5]
};

static const ComplexT K2[order] =
{
	lambda[0] * K1[0],
	lambda[1] * K1[1],
	lambda[2] * K1[2],
	lambda[3] * K1[3],
	lambda[4] * K1[4],
	lambda[5] * K1[5]
};

static const ComplexT K3[order] =
{
	lambda[0] * K2[0],
	lambda[1] * K2[1],
	lambda[2] * K2[2],
	lambda[3] * K2[3],
	lambda[4] * K2[4],
	lambda[5] * K2[5]
};

static ComplexT ComputeExponential(unsigned int mode, double t)
{
	// Third order Taylor series expansion of exp(lambda*t) around -ts/2 since t
	// is always in the interval [-ts, 0]

	auto dt = (t - a);
	auto dt2 = dt * dt;
	auto dt3 = dt * dt2;

	return K[mode] + K1[mode] * dt + K2[mode] * dt2 / 2.0 + K3[mode] * dt3 / 6.0;
}

static ComplexT ComputeLinearIntegral(unsigned int mode, double t0, double t1, double a, double b, double T, const LinearFunction & f)
{
	auto K = -f.k * lambda[mode] * t1 + f.k + lambda[mode] * f.m * T;

	auto ea = ComputeExponential(mode, t0 - a);
	auto eb = ComputeExponential(mode, t0 - b);

	return (ea * (a * f.k * lambda[mode] + K) - eb * (b * f.k * lambda[mode] + K)) / (lambda2[mode] * T);
}

static ComplexT ComputeIntegral(unsigned int mode, double t0, double t, double T)
{
	const auto& f1 = GetFunction(t0, T);
	const auto& f2 = GetFunction(t, T);

	if (t > T)
	{
		return
			ComputeLinearIntegral(mode, t0, 0, t0, T, T, f1)
			+ ComputeLinearIntegral(mode, t0, T, T, t, T, f2);
	}
	if (&f1 == &f2)
	{
		return ComputeLinearIntegral(mode, t0, 0, t0, t, T, f1);
	}

	const auto tbreak = f2.omega * T;

	return ComputeLinearIntegral(mode, t0, 0, t0, tbreak, T, f1)
		+ ComputeLinearIntegral(mode, t0, 0, tbreak, t, T, f2);
}

WaveformGenerator::WaveformGenerator()
	: _t(0)
	, _w{ 0,0,0,0,0,0 }
{
	_pFrequencyInput = CreateInputPort();
}

void WaveformGenerator::Update()
{
	const auto T = scale / _pFrequencyInput->Read();
	const auto t0 = _t;
	_t += ts;
	auto y = 0.0;

	for (unsigned int mode = 0; mode < order; ++mode)
	{
		auto integral = ComputeIntegral(mode, t0, _t, T);

		_w[mode] = c1[mode] * _w[mode] + c2[mode] * integral;

		y = y + (C_[mode] * std::conj(_w[mode])).real();
	}

	if (_t > T)
	{
		_t = _t - T;
	}

	Write(2 * y - 1);
}

IInputPort* WaveformGenerator::GetFrequencyInput() const
{
	return _pFrequencyInput;
}
