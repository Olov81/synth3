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

static double GetPitch(const char noteBase, const int octave, const int noteOffset)
{
	const auto noteBaseSemiTonesFromA = GetSemiTonesFromA(noteBase);

	return noteBaseSemiTonesFromA + noteOffset + (octave - 4) * 12;;
}

double Sequencer::GetPitch(std::string note) const
{
	const auto noteBase = note[0];
	const auto octave = std::stoi(note.substr(note.length() - 1, 1), nullptr, 10);
	const auto keySignature = GetKeySignature(note);
	
	return ::GetPitch(noteBase, octave, keySignature + _tune);
}

Sequencer::Sequencer(double ts, double bpm, EventList events, int tune)
	: _ts(ts)
	, _t(0)
	, _bpm(bpm)
	, _events(std::move(events))
	, _currentPitch(0.0)
	, _currentGate(0.0)
	, _portamento(1e-3)
	, _tune(tune)
	, _envelopeFollower(ts)
{
	_pPitchOutput = CreateOutputPort();
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

	_envelopeFollower.TimeInput()->Set(_portamento);
	_pPitchOutput->Write(_envelopeFollower.Update(_currentPitch));
	_pGateOutput->Write(_currentGate);

	_t += _ts;
}

IOutputPort* Sequencer::PitchOutput() const
{
	return _pPitchOutput;
}

IOutputPort* Sequencer::GateOutput() const
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

	_currentPitch = GetPitch(_nextEvent->Note());
	_currentGate = _nextEvent->Velocity();
	_nextEventStartTime = _t + NoteValueToTimeDuration(_nextEvent->Value());
	_noteOffTime = _t + NoteValueToTimeDuration(_nextEvent->Length());
	_portamento = _nextEvent->Portamento();
	++_nextEvent;
}
