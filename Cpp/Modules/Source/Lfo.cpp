#include "Lfo.h"
#include <cmath>
#include <corecrt_math_defines.h>

Lfo::Lfo(const double fs)
	:_ts(1/fs)
	,_f(0.0)
	,_timeSinceReset(0)
	,_flankDetector(1e-3, std::bind(&Lfo::ResetTimer, this), []{})
{
	_pFrequencyInput = CreateInputPort();
	_pAmplitudeInput = CreateInputPort();
	_pOffsetInput = CreateInputPort();
	_pDelayInput = CreateInputPort();
	_pGateInput = CreateInputPort();
}

void Lfo::Update()
{
	_f = _f + _pFrequencyInput->Read();
	_timeSinceReset += _ts;

	_flankDetector.Update(_pGateInput->Read());

	if(_timeSinceReset < _pDelayInput->Read())
	{
		Write(0);
		return;
	}

	const auto a = _pAmplitudeInput->Read();
	const auto offset = _pOffsetInput->Read();

	const auto y = a * std::sin(2 * M_PI * _f * _ts) + offset;

	Write(y);
}

IInputPort* Lfo::FrequencyInput() const
{
	return _pFrequencyInput;
}

IInputPort* Lfo::AmplitudeInput() const
{
	return _pAmplitudeInput;
}

IInputPort* Lfo::OffsetInput() const
{
	return _pOffsetInput;
}

IInputPort* Lfo::DelayInput() const
{	
	return _pDelayInput;
}

IInputPort* Lfo::GateInput() const
{
	return _pGateInput;
}

void Lfo::ResetTimer()
{
	_timeSinceReset = 0;
}
