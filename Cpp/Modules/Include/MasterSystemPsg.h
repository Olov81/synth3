#pragma once
#include "Decimator.h"
#include "PsgNoiseChannel.h"
#include "PsgToneChannel.h"
#include "Framework/Module.h"

class MasterSystemPsg
{
public:

	MasterSystemPsg(double fs);
	
	PsgToneChannel& ChannelOne();
	PsgToneChannel& ChannelTwo();
	PsgToneChannel& ChannelThree();
	PsgNoiseChannel& ChannelFour();
	
	IOutputPort* Output();
	
private:

	PsgToneChannel _channelOne;
	PsgToneChannel _channelTwo;
	PsgToneChannel _channelThree;
	PsgNoiseChannel _channelFour;
	Sum _mixer;
	Gain _outputGain;
	Decimator _decimator;
};


