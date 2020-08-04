#pragma once
#include "Decimator.h"
#include "Gain.h"
#include "PsgNoiseChannel.h"
#include "PsgToneChannel.h"
#include "Sum.h"

class NesPsg
{
public:

	NesPsg(double fs);

	PsgToneChannel& SquareOne();
	PsgToneChannel& SquareTwo();
	PsgToneChannel& Triangle();
	PsgNoiseChannel& Noise();

	IOutputPort* Output();
	
private:

	PsgToneChannel _squareOne;
	PsgToneChannel _squareTwo;
	PsgToneChannel _triangle;
	PsgNoiseChannel _noise;
	Sum _mixer;
	Gain _outputGain;
};
