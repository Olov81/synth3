#include "MulltiOscillator.h"

MultiOscillator::MultiOscillator(size_t numberOfVoices, std::vector<LinearFunction> waveform)
	:_voices(numberOfVoices)
	,_pitchSplitter(numberOfVoices)
	,_mixer(numberOfVoices)
{
	for (size_t n = 0; n < numberOfVoices; ++n)
	{
		auto voice = std::make_shared<Voice>();

		_voices.emplace_back(voice);
		
		_mixer.GetInputPort(n)->Connect(voice->Output());

		voice->PitchInput()->Connect(_pitchSplitter.GetOutput(n));
		voice->DetuneInput()->Set(0.03 * n);
	}
}

IInputPort* MultiOscillator::PitchInput() const
{
	return _pitchSplitter.Input();
}

IOutputPort* MultiOscillator::Output() const
{
	return _mixer.Output();
}

void MultiOscillator::Update()
{

}

MultiOscillator::Voice::Voice()
	: _generator(Waveforms::Sawtooth())
	, _pitchMixer(2)
{
	_pitchToFrequencyConverter.GetInput()->Connect(_pitchMixer.Output());
	_generator.FrequencyInput()->Connect(_pitchToFrequencyConverter.GetOutput());
}

IInputPort* MultiOscillator::Voice::PitchInput()
{
	return _pitchMixer.GetInputPort(0);
}

IInputPort* MultiOscillator::Voice::DetuneInput()
{
	return _pitchMixer.GetInputPort(1);
}

IOutputPort* MultiOscillator::Voice::Output() const
{
	return _generator.GetOutput();
}

void MultiOscillator::Voice::Update()
{	
}
