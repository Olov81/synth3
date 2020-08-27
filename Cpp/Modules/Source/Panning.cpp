#include "Panning.h"

Panning::Panning()
{
	_pInput = CreateInputPort();
	_pPanInput = CreateInputPort();
	_pLeftOutput = CreateOutputPort();
	_pRightOutput = CreateOutputPort();
}

IInputPort* Panning::Input()
{
	return _pInput;
}

IInputPort* Panning::PanInput()
{
	return _pPanInput;
}

IOutputPort* Panning::LeftOutput()
{
	return _pLeftOutput;
}

IOutputPort* Panning::RightOutput()
{
	return _pRightOutput;
}

void Panning::Update()
{
	auto input = _pInput->Read();
	auto pan = std::max(std::min(_pPanInput->Read(), 1.0), -1.0);
	auto adjustedPan = (pan + 1) / 2;
	auto left = adjustedPan < 1 ? 1 : 1 - adjustedPan;
	auto right = adjustedPan > 1 ? 1 : 1 + adjustedPan;
	
	_pLeftOutput->Write(left * input);
	_pRightOutput->Write(right * input);
}
