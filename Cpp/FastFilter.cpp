
#include "FastFilter.h"
#include <iostream>

void fastFilter(unsigned int bufferSize,
   unsigned int delayBufferSize,
   const double* x,
   const double* B,
   const double* A,
   double* inputState,
   double* outputState,
   unsigned int* index,
   double* y)
{
   unsigned int i = *index;

   for (unsigned int n = 0; n < bufferSize; ++n)
   {
      inputState[i] = x[n];
      y[n] = 0;

      for (unsigned int k = 0; k < delayBufferSize; ++k)
      {
         unsigned int delayIndex = (i + k + 1) % delayBufferSize;
         unsigned int coefficientIndex = (n+1)*delayBufferSize - k - 1;

         y[n] = y[n] + B[coefficientIndex] * inputState[delayIndex];

         if (delayIndex != i)
         {
            y[n] = y[n] - A[coefficientIndex] * outputState[delayIndex];
         }
      }

      y[n] = y[n] / A[n*delayBufferSize];

      outputState[i] = y[n];

      i = (i + 1) % delayBufferSize;
   }

   *index = i;
}
