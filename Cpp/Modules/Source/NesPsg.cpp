#include "NesPsg.h"

NesPsg::NesPsg(double fs)
: _squareOne(fs, Waveforms::Square(), 2)
, _squareTwo(fs, Waveforms::Square(), 2)
, _triangle(fs, Waveforms::Triangle(), 8)
, _noise(fs, 4)
, _mixer(4)
{	
	_mixer.GetInputPort(0)->Connect(_squareOne.Output());
	_mixer.GetInputPort(1)->Connect(_squareTwo.Output());
	_mixer.GetInputPort(2)->Connect(_triangle.Output());
	_mixer.GetInputPort(3)->Connect(_noise.Output());

	_outputGain.GetInput()->Connect(_mixer.Output());
	_outputGain.GetGainInput()->Set(0.35);
}

PsgToneChannel& NesPsg::SquareOne()
{
	return _squareOne;
}

PsgToneChannel& NesPsg::SquareTwo()
{
	return _squareTwo;
}

PsgToneChannel& NesPsg::Triangle()
{
	return _triangle;
}

PsgNoiseChannel& NesPsg::Noise()
{
	return _noise;
}

IOutputPort* NesPsg::Output()
{
	return _outputGain.GetOutput();
}
