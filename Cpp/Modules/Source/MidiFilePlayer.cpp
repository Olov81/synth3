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

IOutputPort* MidiFilePlayer::CreateMidiControlOutput(int controlNumber)
{
	auto* pOutputPort = CreateOutputPort();
	_controllerMap.insert(ControllerMap::value_type(controlNumber, pOutputPort));
	return pOutputPort;
}

void MidiFilePlayer::Update()
{
	if (_midiFile.getEventCount(3) > _eventIndex)
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
			else if(_nextEvent.isController())
			{
				auto output = _controllerMap.find(_nextEvent.getControllerNumber());

				if(output != _controllerMap.end())
				{
					output->second->Write(_nextEvent.getControllerValue() / 127.0);
				}
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
	return _midiFile.getEvent(3, _eventIndex++);
}
