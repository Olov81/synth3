#include "MidiFilePlayer.h"

MidiFilePlayer::MidiFilePlayer(const std::string& fileName, double ts)
	: _midiFile(fileName)
	, _ts(ts)
	, _t(0)
	, _eventIndex(0)
	, _numberOfNotesPlaying(0)
	, _currentPitch(0.0)
{
	_pGateOutput = CreateOutputPort();
	_pPitchOutput = CreateOutputPort();
	_midiFile.doTimeAnalysis();
	_nextEvent = GetNextEvent();
}

IOutputPort* MidiFilePlayer::GateOutput()
{
	return _pGateOutput;
}

IOutputPort* MidiFilePlayer::PitchOutput()
{
	return _pPitchOutput;
}

void MidiFilePlayer::Update()
{
	if (_midiFile.getEventCount(1) > _eventIndex)
	{
		if (_t >= _nextEvent.seconds)
		{
			if (_nextEvent.isNoteOn())
			{
				++_numberOfNotesPlaying;
				_currentPitch = _nextEvent.getKeyNumber() - 69.0;
			}
			else if (_nextEvent.isNoteOff())
			{
				--_numberOfNotesPlaying;
			}

			_nextEvent = GetNextEvent();
		}
	}

	_pGateOutput->Write(_numberOfNotesPlaying > 0 ? 1.0 : 0.0);
	_pPitchOutput->Write(_currentPitch);
	
	_t += _ts;
}

smf::MidiEvent MidiFilePlayer::GetNextEvent()
{
	return _midiFile.getEvent(1, _eventIndex++);
}
