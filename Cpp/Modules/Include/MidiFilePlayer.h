#pragma once
#include <string>
#include <map>
#include "MidiFile.h"
#include "Framework/Module.h"

class MidiFilePlayer : public Module
{
public:

	MidiFilePlayer(const std::string& fileName, double ts, int channel);

	IOutputPort* GateOutput();

	IOutputPort* PitchOutput();

	IOutputPort* CreateMidiControlOutput(int controlNumber);
	
    void Update() override;

private:

	IOutputPort* _pGateOutput;
	IOutputPort* _pPitchOutput;
	
	smf::MidiFile _midiFile;
	int _channel;
	
	typedef std::map<int, IOutputPort*> ControllerMap;
	ControllerMap _controllerMap;
	
	double _ts;
	double _t;
	int _eventIndex;
	smf::MidiEvent _nextEvent;
	int _numberOfNotesPlaying;

	smf::MidiEvent GetNextEvent();
};
