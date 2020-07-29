#pragma once
#include <string>
#include "MidiFile.h"
#include "Framework/Module.h"

class MidiFilePlayer : public Module
{
public:

	MidiFilePlayer(const std::string& fileName, double ts);

	IOutputPort* GateOutput();

	IOutputPort* PitchOutput();
	
    void Update() override;

private:

	IOutputPort* _pGateOutput;
	IOutputPort* _pPitchOutput;
	
	smf::MidiFile _midiFile;

	double _ts;
	double _t;
	int _eventIndex;
	smf::MidiEvent _nextEvent;
	int _numberOfNotesPlaying;
	double _currentPitch;

	smf::MidiEvent GetNextEvent();
};
