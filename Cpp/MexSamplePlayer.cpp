#include "mex.h"
#include "SamplePlayer.h"

static SamplePlayer* player = 0;

void exitFcn() 
{
  if (player != 0)
  {
    delete player;
  }
}

void mexFunction(int nlhs, 
                 mxArray *plhs[],
                 int nrhs, 
                 const mxArray *prhs[])
{

    if(player == 0)
    {
        player = new SamplePlayer();
        mexAtExit(exitFcn);
    }
    
    unsigned int noSamples = (unsigned int)(mxGetPr(prhs[0])[0]);
    double* decimationFactor = mxGetPr(prhs[1]);    
    double* sample = mxGetPr(prhs[2]);
    double* gate = mxGetPr(prhs[3]);
    
    player->SetSample(sample);
    
    plhs[0] = mxCreateDoubleMatrix(noSamples, 1, mxREAL);
    
    double* y = mxGetPr(plhs[0]);
    
    for(int n = 0; n < noSamples; ++n)
    {
        y[n] = player->Update(decimationFactor[n], gate[n]);
    }
}
