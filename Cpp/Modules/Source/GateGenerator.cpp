#include "GateGenerator.h"
#include <utility>

GateGenerator::GateGenerator(double ts, std::list<GateGeneratorEvent> events, size_t channels)
: _ts(ts)
, _t(0.0)
, _events(std::move(events))
, _nextEvent(_events.begin())
{
}

void GateGenerator::Update()
{
	if(_nextEvent == _events.end())
	{
		
	}
}
