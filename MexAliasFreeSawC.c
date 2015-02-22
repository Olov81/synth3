#include "mex.h"
#include "AliasFreeSawC.h"

void mexFunction(int nlhs, 
                 mxArray *plhs[],
                 int nrhs, 
                 const mxArray *prhs[])
{
    unsigned int noSamples = (unsigned int)(mxGetPr(prhs[0])[0]);
    double* f = mxGetPr(prhs[1]);    
    double phase = mxGetPr(prhs[2])[0];
    double* y = 0;
            
    plhs[0] = mxCreateDoubleMatrix(noSamples, 1, mxREAL); 
   
    y = mxGetPr(plhs[0]);
    
    GenerateSaw(noSamples, phase, f, y);
}

