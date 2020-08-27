#include "ControlSignalGenerator.h"

Node::Node(double _time, double _value)
: time(_time)
, value(_value)
{
}

ControlSignalGenerator::ControlSignalGenerator(double ts, std::initializer_list<Node> nodes)
: _ts(ts)
, _nodes(nodes)
{
}

void ControlSignalGenerator::Update()
{
	if(_nodes.size() == _currentNode)
	{
		return;
	}
	
	if(_t > _nodes[_currentNode].time)
	{
		Write(_nodes[_currentNode].value);
		
		++_currentNode;
	}

	_t += _ts;
}
