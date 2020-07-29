#include "MidiFilePlayer.h"

MidiFilePlayer::MidiFilePlayer(const std::string& fileName, double ts)
	: _midiFile(fileName)
	, _ts(ts)
	, _t(0)
	, _eventIndex(0)
	, _currentEventTime(0)
	, _numberOfNotesPlaying(0)
	, _currentPitch(0.0)
{
	_pGateOutput = CreateOutputPort();
	_pPitchOutput = CreateOutputPort();
	_midiFile.doTimeAnalysis();
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
		if (_currentEventTime <= _t)
		{
			auto event = _midiFile.getEvent(1, _eventIndex++);

			if (event.isNoteOn())
			{
				++_numberOfNotesPlaying;
				_currentPitch = event.getKeyNumber() - 64.0;
			}
			else if (event.isNoteOff())
			{
				--_numberOfNotesPlaying;
			}

			_currentEventTime = event.seconds;
		}
	}

	_pGateOutput->Write(_numberOfNotesPlaying > 0 ? 1.0 : 0.0);
	_pPitchOutput->Write(_currentPitch);
	
	_t += _ts;
}
