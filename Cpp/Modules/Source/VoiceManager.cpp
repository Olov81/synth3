#include "VoiceManager.h"

VoiceManager::VoiceManager(std::vector<std::shared_ptr<Voice>> voices)
{
	for (auto voice : voices)
	{
		_freeVoices.push(voice);
	}
}

void VoiceManager::NoteOn(int key, int velocity)
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

void VoiceManager::NoteOff(int key)
{
	const auto numberOfOccupiedVoices = _occupiedVoices.size();

	for (size_t n = 0; n < numberOfOccupiedVoices; ++n)
	{
		auto voice = _occupiedVoices.front();
		_occupiedVoices.pop();

		if (voice.first == key)
		{
			voice.second->NoteOff();
			_freeVoices.push(voice.second);
		}
		else
		{
			_occupiedVoices.push(voice);
		}
	}
}
