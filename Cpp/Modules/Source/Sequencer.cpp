#include "Sequencer.h"
#include <regex>
#include <utility>

static int GetKeySignature(std::string note)
{
	if(note.length() == 3)
	{
		return note[1] == '#' ? 1 : -1;
	}

	return 0;
}

static int GetSemiTonesFromA(const char noteBase)
{
	switch (std::tolower(noteBase))
	{
	case 'c': return -9;
	case 'd': return -7;
	case 'e': return -5;
	case 'f': return -4;
	case 'g': return -2;
	case 'a': return 0;
	case 'b': return 2;
	default: throw std::exception("Invalid note");
	}
}

static double GetFrequency(const char noteBase, const int octave, const int keySignature)
{
	static double frequencyA4 = 440;

	const auto noteBaseSemiTonesFromA = GetSemiTonesFromA(noteBase);

	const double semiTones = noteBaseSemiTonesFromA + keySignature + (octave - 4) * 12;

	return frequencyA4 * std::pow(2.0, semiTones / 12.0);
}

static double GetFrequency(std::string note)
{
	const auto noteBase = note[0];
	const auto octave = std::stoi(note.substr(note.length() - 1, 1), nullptr, 10);
	const auto keySignature = GetKeySignature(note);
	
	return GetFrequency(noteBase, octave, keySignature);
}

Sequencer::Sequencer(double ts, double bpm, EventList events)
	: _ts(ts)
	, _t(0)
	, _bpm(bpm)
	, _events(std::move(events))
	, _currentFrequency(440)
	, _currentGate(0.0)
{
	_pFrequencyOutput = CreateOutputPort();
	_pGateOutput = CreateOutputPort();
	_nextEvent = _events.begin();
	ReadNextEvent();
}

void Sequencer::Update()
{
	if (_t > _nextEventStartTime)
	{
		ReadNextEvent();
	}
	else if (_t > _noteOffTime)
	{
		_currentGate = 0;
	}

	_pFrequencyOutput->Write(_currentFrequency);
	_pGateOutput->Write(_currentGate);

	_t += _ts;
}

IOutputPort* Sequencer::GetFrequencyOutput() const
{
	return _pFrequencyOutput;
}

IOutputPort* Sequencer::GetGateOutput() const
{
	return _pGateOutput;
}

double Sequencer::NoteValueToTimeDuration(double value) const
{
	const auto beatValue = 1.0 / 4.0;
	const auto timePerBeat = 60 / _bpm;
	const auto timePerWholeNote = timePerBeat / beatValue;

	return value * timePerWholeNote;
}

void Sequencer::ReadNextEvent()
{
	if(_nextEvent == _events.end())
	{
		return;
	}

	_currentFrequency = GetFrequency(_nextEvent->Note());
	_currentGate = _nextEvent->Velocity();
	_nextEventStartTime = _t + NoteValueToTimeDuration(_nextEvent->Value());
	_noteOffTime = _t + NoteValueToTimeDuration(_nextEvent->Length());
	++_nextEvent;
}
