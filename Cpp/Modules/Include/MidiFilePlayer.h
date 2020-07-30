#pragma once
#include <functional>
#include <string>
#include <map>
#include "MidiFile.h"
#include "Framework/Module.h"

class MidiTrack : Module
{
public:

	MidiTrack(double ts, smf::MidiEventList eventList);

	void Update() override;
		
	IOutputPort* GateOutput() const;
	IOutputPort* PitchOutput() const;
	IOutputPort* GetMidiControlOutput(int controlNumber);

private:

	double _ts;
	smf::MidiEventList _eventList;
	typedef std::map<int, IOutputPort*> ControllerMap;
	ControllerMap _controllerMap;
	IOutputPort* _pGatePort;
	IOutputPort* _pPitchPort;
	int _numberOfNotesPlaying = 0;
	int _eventNumber = 0;
	double _t = 0;
};

class MidiFilePlayer
{
public:

	MidiFilePlayer(const std::string& fileName, double ts);

	MidiTrack CreateTrack(int track);

private:
	
	smf::MidiFile _midiFile;	
	double _ts;
};
