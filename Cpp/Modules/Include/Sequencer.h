#pragma once

#include "Framework/Module.h"
#include <list>
#include <string>

class SequencerEvent
{
public:

	SequencerEvent(const char* note, double value, double length, double velocity)
		: _note(note)
		, _value(value)
		, _length(length)
		, _velocity(velocity)
	{

	}

	std::string Note() const
	{
		return _note;
	}

	double Value() const
	{
		return _value;
	}

	double Length() const
	{
		return _length;
	}

	double Velocity() const
	{
		return _velocity;
	}

private:

	std::string _note;
	double _value;
	double _length;
	double _velocity;
};

class Sequencer : public Module
{
public:

	typedef std::list<SequencerEvent> EventList;

	Sequencer(double ts, double bpm, EventList events, int tune = 0);

	void Update() override;

	IOutputPort* PitchOutput() const;

	IOutputPort* GateOutput() const;

private:	
	
	double NoteValueToTimeDuration(double value) const;

	void ReadNextEvent();

	double GetPitch(std::string note) const;

	EventList _events;
	EventList::const_iterator _nextEvent;
	double _t;
	double _ts;
	double _bpm;
	double _currentGate;
	double _currentPitch;
	double _nextEventStartTime;
	double _noteOffTime;
	IOutputPort* _pPitchOutput;
	IOutputPort* _pGateOutput;
	int _tune;
};


