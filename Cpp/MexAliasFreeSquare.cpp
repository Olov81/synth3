#include "mex.h"
#include "WaveformGenerator.h"

void mexFunction(int nlhs, 
                 mxArray *plhs[],
                 int nrhs, 
                 const mxArray *prhs[])
{
    unsigned int noSamples = (unsigned int)(mxGetPr(prhs[0])[0]);
    double* f = mxGetPr(prhs[1]);    
    double phase = mxGetPr(prhs[2])[0];
                
    plhs[0] = mxCreateDoubleMatrix(noSamples, 1, mxREAL); 
   
    double* y = mxGetPr(plhs[0]);
    
    GenerateSquare(noSamples, phase, f, y);
}

