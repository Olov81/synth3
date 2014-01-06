#include <complex>
#include <cmath>

using namespace std;

static const double scale = 1000.0;
static const unsigned int order = 6;
static const double fs = 44100.0/scale;
static const double ts = 1.0/fs;

typedef complex<double> ComplexT;

ComplexT lambda[order];
ComplexT c1[order];
ComplexT c2[order];
ComplexT C_[order];
ComplexT w[order] = {0,0,0,0,0,0};
ComplexT I[order];

void initVectors()
{
	lambda[0] = 1.0e+02*ComplexT(-0.056813040537880, + 1.381551184669752);
	lambda[1] = 1.0e+02*ComplexT(-0.056813040537880, - 1.381551184669752);
	lambda[2] = 1.0e+02*ComplexT(-0.205183221961769, + 1.112867309348282);
	lambda[3] = 1.0e+02*ComplexT(-0.205183221961769, - 1.112867309348282);
	lambda[4] = 1.0e+02*ComplexT(-0.376086358629678, + 0.454958427219349);
	lambda[5] = 1.0e+02*ComplexT(-0.376086358629678, - 0.454958427219349);

	c1[0] = ComplexT(-0.879091154523310, + 0.007756886153285);
	c1[1] = ComplexT(-0.879091154523310, - 0.007756886153285);
	c1[2] = ComplexT(-0.511786748657514, + 0.363890848209875);
	c1[3] = ComplexT(-0.511786748657514, - 0.363890848209875);
	c1[4] = ComplexT( 0.218821384956163, + 0.365758489769105);
	c1[5] = ComplexT( 0.218821384956163, - 0.365758489769105);

	c2[0] = 1.0e-04*ComplexT(-0.253030297427751, - 0.634253797829068);
	c2[1] = 1.0e-04*ComplexT(-0.253030297427751, + 0.634253797829068);
	c2[2] = 1.0e-04*ComplexT(-0.169694237927829, - 0.773503425666592);
	c2[3] = 1.0e-04*ComplexT(-0.169694237927830, + 0.773503425666592);
	c2[4] = 1.0e-04*ComplexT(-0.083348029481645, + 0.079854931551413);
	c2[5] = 1.0e-04*ComplexT(-0.083348029481645, - 0.079854931551413);

	C_[0] = 1.0e+02*ComplexT(-0.015262725760909, - 0.042948389151723);
	C_[1] = 1.0e+02*ComplexT(-0.015262725760909, + 0.042948389151723);
	C_[2] = 1.0e+02*ComplexT( 0.201429115916261, + 0.076086618368018);
	C_[3] = 1.0e+02*ComplexT( 0.201429115916261, - 0.076086618368018);
	C_[4] = 1.0e+02*ComplexT(-4.753013422962410, - 9.189630137342540);
	C_[5] = 1.0e+02*ComplexT(-4.753013422962410, + 9.189630137342540);
}

void GenerateSaw(unsigned int N,
                 double phase,
				 const double* f,
				 double* y)
{
	initVectors();

	double t = scale*phase/f[0];
	double t0 = 0.0;
	double k = 0.0;
	double T = 0.0;

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
				I[i] = (lambda[i]*t0 + 1.0)*exp(lambda[i]*(t-t0)) + (1.0 - exp(lambda[i]*(t-T)))*lambda[i]*T - lambda[i]*t - 1.0;

				w[i] = c1[i]*w[i] + k*c2[i]*I[i];

				y[n] = y[n] + (C_[i]*w[i]).real();
			}
        
			t = t - T;
		}
		else
		{
			for( unsigned int i = 0; i < order; ++i )
			{
				I[i] = (lambda[i]*t0 + 1.0)*c1[i] - lambda[i]*t - 1.0;

				w[i] = c1[i]*w[i] + k*c2[i]*I[i];

				y[n] = y[n] + (C_[i]*w[i]).real();
			}
		}

		y[n] = 2*y[n] - 1;
        
        t0 = t;
		t = t + ts;
	}
}