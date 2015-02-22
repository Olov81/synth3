#include <complex>
#include <cmath>

using namespace std;

static const double scale = 1000.0;
static const unsigned int order = 6;
static const double fs = 44100.0/scale;
static const double ts = 1.0/fs;

typedef complex<double> ComplexT;

static const ComplexT I = ComplexT(0, 1);

static const ComplexT lambda[order] = 
	{
		1.0e+02*(-0.056813040537880 - 1.381551184669752*I),
		1.0e+02*(-0.056813040537880 - 1.381551184669752*I),
		1.0e+02*(-0.205183221961769 + 1.112867309348282*I),
		1.0e+02*(-0.205183221961769 - 1.112867309348282*I),
		1.0e+02*(-0.376086358629678 + 0.454958427219349*I),
		1.0e+02*(-0.376086358629678 - 0.454958427219349*I)
	};

static const ComplexT c1[order] = 
	{
		-0.879091154523310 + 0.007756886153285*I,
		-0.879091154523310 - 0.007756886153285*I,
		-0.511786748657514 + 0.363890848209875*I,
		-0.511786748657514 - 0.363890848209875*I,
		 0.218821384956163 + 0.365758489769105*I,
		 0.218821384956163 - 0.365758489769105*I
	};

static const ComplexT c2[order] =
	{
		1.0e-04*(-0.253030297427751 - 0.634253797829068*I),
		1.0e-04*(-0.253030297427751 + 0.634253797829068*I),
		1.0e-04*(-0.169694237927829 - 0.773503425666592*I),
		1.0e-04*(-0.169694237927830 + 0.773503425666592*I),
		1.0e-04*(-0.083348029481645 + 0.079854931551413*I),
		1.0e-04*(-0.083348029481645 - 0.079854931551413*I)
	};

static const ComplexT C_[order] = 
	{
		1.0e+02*(-0.015262725760909 - 0.042948389151723*I),
		1.0e+02*(-0.015262725760909 + 0.042948389151723*I),
		1.0e+02*( 0.201429115916261 + 0.076086618368018*I),
		1.0e+02*( 0.201429115916261 - 0.076086618368018*I),
		1.0e+02*(-4.753013422962410 - 9.189630137342540*I),
		1.0e+02*(-4.753013422962410 + 9.189630137342540*I)
	};

void GenerateSaw(unsigned int N,
                 double phase,
				 const double* f,
				 double* y)
{
	double t = scale*phase/f[0];
	double t0 = 0.0;
	double k = 0.0;
	double T = 0.0;
	ComplexT w[order] = {0,0,0,0,0,0};
	ComplexT Integral;

	for( unsigned long n = 0; n < N; ++n )
	{
        double f_scaled = f[n]/scale;
        
		T = 1.0/f_scaled;
    
		k = f_scaled;
    
		y[n] = 0;

		if( t > T )
		{
			for( unsigned int i = 0; i < order; ++i )
			{
				Integral = (lambda[i]*t0 + 1.0)*exp(lambda[i]*(t-t0)) + (1.0 - exp(lambda[i]*(t-T)))*lambda[i]*T - lambda[i]*t - 1.0;

				w[i] = c1[i]*w[i] + k*c2[i]*Integral;

				y[n] = y[n] + (C_[i]*w[i]).real();
			}
        
			t = t - T;
		}
		else
		{
			for( unsigned int i = 0; i < order; ++i )
			{
				Integral = (lambda[i]*t0 + 1.0)*c1[i] - lambda[i]*t - 1.0;

				w[i] = c1[i]*w[i] + k*c2[i]*Integral;
				
				y[n] = y[n] + (C_[i]*w[i]).real();
			}
		}

		y[n] = 2*y[n] - 1;
        
        t0 = t;
		t = t + ts;
	}
}