#include "MidiFilePlayer.h"

#include <utility>

MidiTrackBase::MidiTrackBase(
	const double ts,
	smf::MidiEventList eventList,
	double tempoScale)
	:_ts(ts)
	, _eventList(std::move(eventList))
	, _tempoScale(tempoScale)
{
}

void MidiTrackBase::Update()
{
	if (_eventNumber >= _eventList.size())
	{
		return;
	}

	const auto nextEvent = _eventList[_eventNumber];

	if (_t >= nextEvent.seconds / _tempoScale)
	{		
		if (nextEvent.isController())
		{
			auto* pControlOutput = GetMidiControlOutput(nextEvent.getControllerNumber());

			pControlOutput->Write(nextEvent.getControllerValue() / 127.0);
		}
		else
		{
			OnEvent(nextEvent);
		}

		++_eventNumber;
	}

	_t += _ts;
}

IOutputPort* MidiTrackBase::GetMidiControlOutput(int controlNumber, double initialValue)
{
	if (_controllerMap.find(controlNumber) == _controllerMap.end())
	{
		auto* pOutput = CreateOutputPort();
		pOutput->Write(initialValue);
		_controllerMap.insert(ControllerMap::value_type(controlNumber, pOutput));
	}

	return _controllerMap[controlNumber];
}

MidiTrack::MidiTrack(
	const double ts,
	smf::MidiEventList eventList,
	double tempoScale,
	size_t polyphony)
: MidiTrackBase(ts, eventList, tempoScale)
, _voiceSplitter(polyphony, [this]() {return this->CreateOutputPort(); })
{
}

Voice& MidiTrack::Voice(size_t index)
{
	return _voiceSplitter.GetVoice(index);
}

void MidiTrack::OnEvent(const smf::MidiEvent& midiEvent)
{
	if (midiEvent.isNoteOn())
	{
		_voiceSplitter.NoteOn(midiEvent.getKeyNumber(), midiEvent.getVelocity());
	}
	else if (midiEvent.isNoteOff())
	{
		_voiceSplitter.NoteOff(midiEvent.getKeyNumber());
	}
}

MidiDrumTrack::MidiDrumTrack(
	const double ts,
	smf::MidiEventList eventList,
	double tempoScale)
	: MidiTrackBase(ts, eventList, tempoScale)
{
}

void MidiDrumTrack::OnEvent(const smf::MidiEvent& midiEvent)
{
	if (midiEvent.isNoteOn())
	{
		GetGateOutput(midiEvent.getKeyNumber())->Write(midiEvent.getVelocity() / 127.0);
	}
	else if(midiEvent.isNoteOff())
	{
		GetGateOutput(midiEvent.getKeyNumber())->Write(0.0);
	}
}

IOutputPort* MidiDrumTrack::GetGateOutput(int note)
{
	if(_noteMap.find(note) == _noteMap.end())
	{
		_noteMap.insert(NoteMap::value_type(note, CreateOutputPort()));
	}
	
	return _noteMap[note];
}

MidiFilePlayer::MidiFilePlayer(const std::string& fileName, double ts, double tempoScale)
	: _midiFile(fileName)
	, _ts(ts)
	,_tempoScale(tempoScale)
{
	_midiFile.doTimeAnalysis();
}

MidiTrack MidiFilePlayer::CreateTrack(int track, size_t polyphony)
{
	return MidiTrack(_ts, _midiFile[track], _tempoScale, polyphony);
}

MidiDrumTrack MidiFilePlayer::CreateDrumTrack(int track)
{
	return MidiDrumTrack(_ts, _midiFile[track], _tempoScale);
}
