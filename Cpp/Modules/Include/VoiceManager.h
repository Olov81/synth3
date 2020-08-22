#pragma once
#include <memory>
#include <queue>
#include <vector>
#include "Voice.h"

class VoiceManager
{
public:

	VoiceManager(std::vector<std::shared_ptr<Voice>> voices);

	void NoteOn(int key, int velocity);

	void NoteOff(int key);

private:

	std::queue<std::shared_ptr<Voice>> _freeVoices;
	std::queue<std::pair<int, std::shared_ptr<Voice>>> _occupiedVoices;
};
