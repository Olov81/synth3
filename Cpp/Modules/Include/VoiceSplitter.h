#pragma once
#include <memory>
#include <queue>
#include <vector>
#include "Voice.h"

class VoiceSplitter
{
public:

	VoiceSplitter(size_t numberOfVoices);

	Voice& GetVoice(size_t index);

	void NoteOn(int key, int velocity);

	void NoteOff(int key);

private:

	std::vector<std::shared_ptr<Voice>> _voices;
	std::queue<std::shared_ptr<Voice>> _freeVoices;
	std::queue<std::pair<int, std::shared_ptr<Voice>>> _occupiedVoices;
};
