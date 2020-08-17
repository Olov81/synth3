#pragma once
#include <string>
#include <map>
#include "MidiFile.h"
#include "VoiceSplitter.h"
#include "Framework/Module.h"

class MidiTrackBase : public Module
{
public:

	MidiTrackBase(double ts, smf::MidiEventList eventList, double tempoScale);
	
	void Update() override;
	
	IOutputPort* GetMidiControlOutput(int controlNumber, double initialValue = 0.0);

private:

	double _ts;
	smf::MidiEventList _eventList;
	double _tempoScale;
	int _eventNumber = 0;
	double _t = 0;
	typedef std::map<int, IOutputPort*> ControllerMap;
	ControllerMap _controllerMap;

	virtual void OnEvent(const smf::MidiEvent& midiEvent) = 0;
};

class MidiTrack : public MidiTrackBase
{
public:

	MidiTrack(double ts, smf::MidiEventList eventList, double tempoScale, size_t polyphony);

	Voice& Voice(size_t index);

private:

	VoiceSplitter _voiceSplitter;
	
	void OnEvent(const smf::MidiEvent& midiEvent) override;
};

class MidiDrumTrack : public MidiTrackBase
{
public:

	MidiDrumTrack(double ts, smf::MidiEventList eventList, double tempoScale);

	IOutputPort* GetGateOutput(int note);
	
private:

	typedef std::map<int, IOutputPort*> NoteMap;
	NoteMap _noteMap;

	void OnEvent(const smf::MidiEvent& midiEvent) override;
};

class MidiFilePlayer
{
public:

	MidiFilePlayer(const std::string& fileName, double ts, double tempoScale = 1.0);

	MidiTrack CreateTrack(int track, size_t polyphony = 1);

	MidiDrumTrack CreateDrumTrack(int track);

private:
	
	smf::MidiFile _midiFile;	
	double _ts;
	double _tempoScale = 1.0;
};
