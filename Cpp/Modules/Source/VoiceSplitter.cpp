#include "VoiceSplitter.h"

VoiceSplitter::VoiceSplitter(size_t numberOfVoices)
{
	for (size_t n = 0; n < numberOfVoices; ++n)
	{
		auto voice = std::make_shared<Voice>();
		_voices.push_back(voice);
		_freeVoices.push(voice);
	}
}

Voice& VoiceSplitter::GetVoice(size_t index)
{
	return *_voices[index];
}

void VoiceSplitter::NoteOn(int key, int velocity)
{
	if (_freeVoices.empty())
	{
		const auto stolenVoice = _occupiedVoices.front();
		_occupiedVoices.pop();
		stolenVoice.second->NoteOn(key, velocity);
		_occupiedVoices.push(std::make_pair(key, stolenVoice.second));
		return;
	}

	const auto voice = _freeVoices.front();
	voice->NoteOn(key, velocity);
	_occupiedVoices.push(std::make_pair(key, voice));
	_freeVoices.pop();
}

void VoiceSplitter::NoteOff(int key)
{
	const auto numberOfOccupiedVoices = _occupiedVoices.size();

	for (size_t n = 0; n < numberOfOccupiedVoices; ++n)
	{
		auto voice = _occupiedVoices.front();
		_occupiedVoices.pop();

		if (voice.first == key)
		{
			_freeVoices.push(voice.second);
		}
		else
		{
			_occupiedVoices.push(voice);
		}
	}
}
