#include "Lfo.h"
#include <cmath>
#include <corecrt_math_defines.h>

Lfo::Lfo(const double fs)
	:_ts(1/fs)
	,_f(0.0)
{
	_pFrequencyInput = CreateInputPort();
	_pAmplitudeInput = CreateInputPort();
	_pOffsetInput = CreateInputPort();
}

void Lfo::Update()
{
	_f = _f + _pFrequencyInput->Read();
	const auto a = _pAmplitudeInput->Read();
	const auto offset = _pOffsetInput->Read();

	const auto y = a * std::sin(2 * M_PI * _f * _ts) + offset;

	Write(y);
}

IInputPort* Lfo::GetFrequencyInput() const
{
	return _pFrequencyInput;
}

IInputPort* Lfo::GetAmplitudeInput() const
{
	return _pAmplitudeInput;
}

IInputPort* Lfo::GetOffsetInput() const
{
	return _pOffsetInput;
}
