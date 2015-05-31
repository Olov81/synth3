#include "mex.h"
#include "FastFilter.h"
#include <memory>

//void mexFunction(int nlhs,
//                 mxArray *plhs[],
//                 int nrhs,
//                 const mxArray *prhs[])
//{
//   const double* B = mxGetPr(prhs[0]);
//   const double* A = mxGetPr(prhs[1]);
//   const double* x = mxGetPr(prhs[2]);
//   const double* inputState = mxGetPr(prhs[3]);
//   const double* outputState = mxGetPr(prhs[4]);
//   const double* index = mxGetPr(prhs[5]);
//
//   unsigned int bufferSize = mxGetNumberOfElements(prhs[2]);
//   unsigned int delayBufferSize = mxGetNumberOfElements(prhs[0])/bufferSize;
//
//   plhs[0] = mxCreateDoubleMatrix(bufferSize, 1, mxREAL);
//   plhs[1] = mxCreateDoubleMatrix(delayBufferSize, 1, mxREAL);
//   plhs[2] = mxCreateDoubleMatrix(delayBufferSize, 1, mxREAL);
//   plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
//
//   memcpy(mxGetPr(plhs[1]), inputState, delayBufferSize);
//   memcpy(mxGetPr(plhs[2]), outputState, delayBufferSize);
//
//   double* y = mxGetPr(plhs[0]);
//
//   unsigned int i = static_cast<unsigned int>(index[0]);
//
//   fastFilter(
//      bufferSize, 
//      delayBufferSize,
//      x,
//      B,
//      A,
//      mxGetPr(plhs[1]),
//      mxGetPr(plhs[2]),
//      &i,
//      y);
//
//   memcpy(mxGetPr(plhs[3]), &i, 1);
//}

void mexFunction(int nlhs,
   mxArray *plhs[],
   int nrhs,
   const mxArray *prhs[])
{
   double* B = mxGetPr(prhs[0]);
   double* A = mxGetPr(prhs[1]);
   double* x = mxGetPr(prhs[2]);
   double* inputState = mxGetPr(prhs[3]);
   double* outputState = mxGetPr(prhs[4]);
   double* index = mxGetPr(prhs[5]);

   unsigned int bufferSize = mxGetNumberOfElements(prhs[2]);
   unsigned int delayBufferSize = mxGetNumberOfElements(prhs[0]) / bufferSize;

   plhs[0] = mxCreateDoubleMatrix(bufferSize, 1, mxREAL);

   double* y = mxGetPr(plhs[0]);

   unsigned int i = static_cast<unsigned int>(index[0]);

   fastFilter(
      bufferSize,
      delayBufferSize,
      x,
      B,
      A,
      inputState,
      outputState,
      &i,
      y);

   index[0] = i;
   //plhs[1] = inputState;
   //plhs[2] = mxCreateDoubleMatrix(delayBufferSize, 1, mxREAL);
   //plhs[3] = mxCreateDoubleMatrix(1, 1, mxREAL);
   
}
