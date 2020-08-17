#pragma once
#include "BitCrusher.h"
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
	BitCrusher _bitCrusher;
};


