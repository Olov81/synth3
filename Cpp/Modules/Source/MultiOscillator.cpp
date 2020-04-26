#include "MulltiOscillator.h"

MultiOscillator::MultiOscillator(
	size_t numberOfVoices,
	std::vector<LinearFunction> waveform,
	double voiceInterval)
	:_voices(numberOfVoices)
	,_pitchSplitter(numberOfVoices)
	,_mixer(numberOfVoices)
{
	_detuneRepeater.GetGainInput()->Set(1);

	for (size_t n = 0; n < numberOfVoices; ++n)
	{
		auto transpose = (n % 2) * voiceInterval;

		auto voice = std::make_shared<Voice>(waveform, n, transpose);

		_voices.emplace_back(voice);
		
		_mixer.GetInputPort(n)->Connect(voice->Output());

		voice->PitchInput()->Connect(_pitchSplitter.GetOutput(n));
		voice->DetuneInput()->Connect(_detuneRepeater.GetOutput());
	}
}

IInputPort* MultiOscillator::PitchInput() const
{
	return _pitchSplitter.Input();
}

IInputPort* MultiOscillator::DetuneInput()
{
	return _detuneRepeater.GetInput();
}

IOutputPort* MultiOscillator::Output() const
{
	return _mixer.Output();
}

void MultiOscillator::Update()
{

}

MultiOscillator::Voice::Voice(
	std::vector<LinearFunction> waveform,
	double detuneMultiplicator,
	double transpose)
	: _generator(waveform)
	, _pitchMixer(3)
{
	_detuneGain.GetGainInput()->Set(detuneMultiplicator);
	_pitchMixer.GetInputPort(1)->Connect(_detuneGain.GetOutput());
	_pitchMixer.GetInputPort(2)->Set(transpose);
	_pitchToFrequencyConverter.GetInput()->Connect(_pitchMixer.Output());
	_generator.FrequencyInput()->Connect(_pitchToFrequencyConverter.GetOutput());
}

IInputPort* MultiOscillator::Voice::PitchInput()
{
	return _pitchMixer.GetInputPort(0);
}

IInputPort* MultiOscillator::Voice::DetuneInput()
{
	return _detuneGain.GetInput();
}

IOutputPort* MultiOscillator::Voice::Output() const
{
	return _generator.GetOutput();
}

void MultiOscillator::Voice::Update()
{	
}
