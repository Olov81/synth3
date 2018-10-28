#include <complex>
#include <cmath>

using namespace std;

static const double scale = 1000.0;
static const unsigned int order = 6;
static const double fs = 44100.0 / scale;
static const double ts = 1.0 / fs;

typedef complex<double> ComplexT;

static const ComplexT I = ComplexT(0, 1);

// 20 kHz
static const ComplexT lambda[order] =
{

    1.0e+02*(-0.051531102528688 + 1.253107650494106*I),
    1.0e+02*(-0.051531102528688 - 1.253107650494106*I),
    1.0e+02*(-0.186107230804326 + 1.009403455191187*I),
    1.0e+02*(-0.186107230804326 - 1.009403455191187*I),
    1.0e+02*(-0.341121413723065 + 0.412660704960861*I),
    1.0e+02*(-0.341121413723065 - 0.412660704960861*I)
};

static const ComplexT c1[order] =
{
    -0.849959499022492 + 0.262996584567710*I,
    -0.849959499022492 - 0.262996584567710*I,
    -0.431438602440959 + 0.493799212745242*I,
    -0.431438602440959 - 0.493799212745242*I,
     0.273705895647727 + 0.371433865175301*I,
     0.273705895647727 - 0.371433865175301*I
};

static const ComplexT c2[order] =
{
    -0.653464062005352 - 0.960363444341962*I,
    -0.653464062005352 + 0.960363444341962*I,
     0.430418280636391 + 0.506874822688097*I,
     0.430418280636391 - 0.506874822688097*I,
     0.000324855944613 + 0.018554018695005*I,
     0.000324855944613 - 0.018554018695005*I
};

static const ComplexT C_[order] =
{
    1.0e+02*(-0.013843664160728 + 0.038955235452340*I),
    1.0e+02*(-0.013843664160728 - 0.038955235452340*I),
    1.0e+02*(-0.182700608492865 + 0.069012225024015*I),
    1.0e+02*(-0.182700608492865 - 0.069012225024015*I),
    1.0e+02*(-4.310989922168807 + 8.335007580485707*I),
    1.0e+02*(-4.310989922168807 - 8.335007580485707*I)
};

//// 5 kHz
//static const ComplexT lambda[order] =
//{
//    - 1.288277563217196 + 31.327691262352658*I,
//    - 1.288277563217196 - 31.327691262352658*I,
//    - 4.652680770108146 + 25.235086379779673*I,
//    - 4.652680770108146 - 25.235086379779673*I,
//    - 8.528035343076617 + 10.316517624021536*I,
//    - 8.528035343076617 - 10.316517624021536*I
//};
//
//static const ComplexT c1[order] =
//{
//    0.736288917612358 + 0.633346146397530*I,
//    0.736288917612358 - 0.633346146397530*I,
//    0.756521015127202 + 0.487283508962141*I,
//    0.756521015127202 - 0.487283508962141*I,
//    0.801720311712290 + 0.191047994199341*I,
//    0.801720311712290 - 0.191047994199341*I
//};
//
////static const ComplexT c2[order] =
////{
////    -0.000492333449630 - 0.001234098696484*I,
////    -0.000492333449630 + 0.001234098696484*I,
////     0.000330261044208 + 0.001505402022946*I,
////     0.000330261044208 - 0.001505402022946*I,
////    -0.000162527039178 + 0.000155715566037*I,
////    -0.000162527039178 - 0.000155715566037*I
////};
//
//static const ComplexT c2[order] =
//{
//    -0.509144455456107 + 1.161944268513443*I,
//    -0.509144455456106 - 1.161944268513445*I,
//     0.602779839844918 - 0.686002034087838*I,
//     0.602779839844918 + 0.686002034087839*I,
//     0.021897396717803 + 0.025001330692869*I,
//     0.021897396717803 - 0.025001330692869*I
//};
//
//static const ComplexT C_[order] =
//{
//    1.0e+02*(- 0.003459265321922 + 0.009734163841526*I),
//    1.0e+02*(- 0.003459265321922 - 0.009734163841526*I),
//    1.0e+02*(- 0.045642621696783 + 0.017240768409085*I),
//    1.0e+02*(- 0.045642621696783 - 0.017240768409085*I),
//    1.0e+02*(- 1.074922969523174 + 2.078290894010360*I),
//    1.0e+02*(- 1.074922969523174 - 2.078290894010360*I)
//};

ComplexT ComputeSawtoothIntegral(unsigned int mode, double t0, double t, double T)
{
    ComplexT lmbda = lambda[mode];

    if (t > T)
    {
        return ((lmbda * t0 + 1.0)*exp(lmbda * (t - t0)) + (1.0 - exp(lmbda * (t - T)))*lmbda * T - lmbda * t - 1.0)/(T*c1[mode]*lmbda*lmbda);
    }

    return ((lmbda * t0 + 1.0)*c1[mode] - lmbda * t - 1.0)/(T*c1[mode]*lmbda*lmbda);
}

ComplexT ComputeSquarewaveIntegral(unsigned int mode, double t0, double t, double T)
{
    double t1, t2;
    double t_switch = 0.5*T;

    if (t > T)
    {
        t1 = T;
        t2 = t;
    }
    else if (t0 < t_switch && t_switch < t)
    {
        t1 = t0;
        t2 = t_switch;
    }
    else if (t > t_switch)
    {
        return 0.0;
    }
    else
    {
        t1 = t0;
        t2 = t;
    }

    ComplexT lmbda = lambda[mode];

    return (exp(lmbda*(t0 - t1)) - exp(lmbda*(t0 - t2))) / lmbda;
}

typedef ComplexT(*ComputeWaveformIntegral)(unsigned int, double, double, double);

void GenerateWaveform(
    unsigned int N,
    double phase,
    const double* f,
    ComputeWaveformIntegral computeWaveformIntegral,
    double* y)
{
    double t = scale*phase / f[0];
    double t0 = 0.0;
    ComplexT w[order] = { 0,0,0,0,0,0 };

    for (unsigned long n = 0; n < N; ++n)
    {
        y[n] = 0;

        double T = scale / f[n];
        t0 = t;
        t = t + ts;

        for (unsigned int mode = 0; mode < order; ++mode)
        {
            ComplexT integral = computeWaveformIntegral(mode, t0, t, T);

            w[mode] = c1[mode] * w[mode] + c2[mode] * integral;

            y[n] = y[n] + (C_[mode] * std::conj(w[mode])).real();
        }

        if (t > T)
        {
            t = t - T;
        }

        y[n] = 2 * y[n] - 1;
    }
}

void GenerateSaw(
    unsigned int N,
    double phase,
    const double* f,
    double* y)
{
    return GenerateWaveform(N, phase, f, ComputeSawtoothIntegral, y);
}

void GenerateSquare(
    unsigned int N,
    double phase,
    const double* f,
    double* y)
{
    return GenerateWaveform(N, phase, f, ComputeSquarewaveIntegral, y);
}

//void GenerateSaw(unsigned int N,
//    double phase,
//    const double* f,
//    double* y)
//{
//    double t = scale*phase / f[0];
//    double t0 = 0.0;
//    double k = 0.0;
//    double T = 0.0;
//    ComplexT w[order] = { 0,0,0,0,0,0 };
//    ComplexT Integral;
//
//    for (unsigned long n = 0; n < N; ++n)
//    {
//        double f_scaled = f[n] / scale;
//
//        T = 1.0 / f_scaled;
//
//        k = f_scaled;
//
//        y[n] = 0;
//
//        t0 = t;
//        t = t + ts;
//
//        ComplexT out = 0;
//
//        if (t > T)
//        {
//            for (unsigned int i = 0; i < order; ++i)
//            {
//                Integral = (lambda[i] * t0 + 1.0)*exp(lambda[i] * (t - t0)) + (1.0 - exp(lambda[i] * (t - T)))*lambda[i] * T - lambda[i] * t - 1.0;
//
//                w[i] = c1[i] * w[i] + c2[i] * k * Integral;
//
//                out = out + C_[i] * std::conj(w[i]);
//            }
//
//            t = t - T;
//        }
//        else
//        {
//            for (unsigned int i = 0; i < order; ++i)
//            {
//                Integral = (lambda[i] * t0 + 1.0)*c1[i] - lambda[i] * t - 1.0;
//
//                w[i] = c1[i] * w[i] + c2[i] * k* Integral;
//
//                out = out + C_[i] * std::conj(w[i]);
//            }
//        }
//
//        y[n] = 2 * out.real() - 1;
//    }
//}