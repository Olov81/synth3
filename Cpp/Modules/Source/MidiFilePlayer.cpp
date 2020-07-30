#include "MidiFilePlayer.h"

#include <utility>

MidiTrack::MidiTrack(
	const double ts,
	smf::MidiEventList eventList)
:_ts(ts)
, _eventList(std::move(eventList))
{
	_pGatePort = CreateOutputPort();
	_pPitchPort = CreateOutputPort();
}

void MidiTrack::Update()
{
	if(_eventNumber >= _eventList.size())
	{
		return;
	}
	
	const auto nextEvent = _eventList[_eventNumber];
	
	if (_t >= nextEvent.seconds)
	{
		if (nextEvent.isNoteOn())
		{
			_pPitchPort->Write(nextEvent.getKeyNumber() - 69.0);
			_pGatePort->Write(nextEvent.getVelocity() / 127.0);
			++_numberOfNotesPlaying;
		}
		else if (nextEvent.isNoteOff())
		{
			--_numberOfNotesPlaying;

			if(_numberOfNotesPlaying == 0)
			{
				_pGatePort->Write(0);
			}
		}
		else if (nextEvent.isController())
		{
			auto* pControlOutput = GetMidiControlOutput(nextEvent.getControllerNumber());

			pControlOutput->Write(nextEvent.getControllerValue() / 127.0);
		}

		++_eventNumber;
	}

	_t += _ts;
}

IOutputPort* MidiTrack::GateOutput() const
{
	return _pGatePort;
}

IOutputPort* MidiTrack::PitchOutput() const
{
	return _pPitchPort;
}

IOutputPort* MidiTrack::GetMidiControlOutput(int controlNumber, double initialValue)
{
	if(_controllerMap.find(controlNumber) == _controllerMap.end())
	{
		auto* pOutput = CreateOutputPort();
		pOutput->Write(initialValue);
		_controllerMap.insert(ControllerMap::value_type(controlNumber, pOutput));
	}

	return _controllerMap[controlNumber];
}

MidiFilePlayer::MidiFilePlayer(const std::string& fileName, double ts)
	: _midiFile(fileName)
	, _ts(ts)
{
	_midiFile.doTimeAnalysis();
}

MidiTrack MidiFilePlayer::CreateTrack(int track)
{
	return MidiTrack(_ts, _midiFile[track]);
}