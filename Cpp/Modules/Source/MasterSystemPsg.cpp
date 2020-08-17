#include "MasterSystemPsg.h"

MasterSystemPsg::MasterSystemPsg(double fs)
	: _channelOne(fs, Waveforms::Square())
	,_channelTwo(fs, Waveforms::Square())
	,_channelThree(fs, Waveforms::Square())
	,_channelFour(1/fs, 8)
	,_mixer(4)
{
	_mixer.GetInputPort(0)->Connect(_channelOne.Output());
	_mixer.GetInputPort(1)->Connect(_channelTwo.Output());
	_mixer.GetInputPort(2)->Connect(_channelThree.Output());
	_mixer.GetInputPort(3)->Connect(_channelFour.Output());
	
	_outputGain.GetGainInput()->Set(0.35);
	_outputGain.GetInput()->Connect(_mixer.Output());

	_bitCrusher.ResolutionInput()->Set(128);
	_bitCrusher.GetInput()->Connect(_outputGain.GetOutput());
}

PsgToneChannel& MasterSystemPsg::ChannelOne()
{
	return _channelOne;
}

PsgToneChannel& MasterSystemPsg::ChannelTwo()
{
	return _channelTwo;
}

PsgToneChannel& MasterSystemPsg::ChannelThree()
{
	return _channelThree;
}

PsgNoiseChannel& MasterSystemPsg::ChannelFour()
{
	return _channelFour;
}

IOutputPort* MasterSystemPsg::Output()
{
	return _bitCrusher.GetOutput();
}
