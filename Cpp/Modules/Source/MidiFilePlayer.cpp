#include "MidiFilePlayer.h"

MidiFilePlayer::MidiFilePlayer(const std::string& fileName, double ts, int channel)
	: _midiFile(fileName)
	, _channel(channel)
	, _ts(ts)
	, _t(0)
	, _eventIndex(0)
	, _numberOfNotesPlaying(0)
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
	if (_midiFile.getEventCount(_channel) > _eventIndex)
	{
		if (_t >= _nextEvent.seconds)
		{
			if (_nextEvent.isNoteOn())
			{
				++_numberOfNotesPlaying;
				_pPitchOutput->Write(_nextEvent.getKeyNumber() - 69.0);
				_pGateOutput->Write(_nextEvent.getVelocity() / 127.0);
			}
			else if (_nextEvent.isNoteOff())
			{
				--_numberOfNotesPlaying;

				if(_numberOfNotesPlaying == 0)
				{
					_pGateOutput->Write(0.0);
				}
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
	
	_t += _ts;
}

smf::MidiEvent MidiFilePlayer::GetNextEvent()
{
	return _midiFile.getEvent(_channel, _eventIndex++);
}
