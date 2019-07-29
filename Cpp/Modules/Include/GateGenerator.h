#pragma once
#include "Framework/Module.h"
#include <list>



struct GateGeneratorEvent
{
	GateGeneratorEvent(const double& time, const char* noteId, const bool noteOn)
		: _time(time),
		_noteId(noteId),
		_noteOn(noteOn)
	{

	}

	double Time() const
	{
		return _time;
	}

	const char* NoteId() const
	{
		return _noteId;
	}

	bool NoteOn() const
	{
		return _noteOn;
	}

private:

	const double _time;
	const char* _noteId;
	const bool _noteOn;
};

class GateGenerator : Module
{
public:

	GateGenerator(double ts, std::list<GateGeneratorEvent> events, size_t channels);

	void Update() override;

private:

	double _ts;
	double _t;
	std::list<GateGeneratorEvent> _events;
	std::list<GateGeneratorEvent>::const_iterator _nextEvent;
};
