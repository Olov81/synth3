#pragma once
#include <functional>
#include <string>
#include <map>
#include "MidiFile.h"
#include "Framework/Module.h"

class MidiTrack : Module
{
public:

	MidiTrack(double ts, smf::MidiEventList eventList, double tempoScale);

	void Update() override;
		
	IOutputPort* GateOutput() const;
	IOutputPort* PitchOutput() const;
	IOutputPort* GetMidiControlOutput(int controlNumber, double initialValue = 0.0);

private:

	double _ts;
	smf::MidiEventList _eventList;
	double _tempoScale;
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

	MidiFilePlayer(const std::string& fileName, double ts, double tempoScale = 1.0);

	MidiTrack CreateTrack(int track);

private:
	
	smf::MidiFile _midiFile;	
	double _ts;
	double _tempoScale = 1.0;
};
