#pragma once
#include "Source.h"

struct Node
{
	Node(double _time, double _value);

	double time;
	double value;
};

class ControlSignalGenerator : public Source
{
public:

	ControlSignalGenerator(double ts, std::initializer_list<Node> nodes);

	void Update() override;

private:

	double _ts;
	std::vector<Node> _nodes;
	double _t = 0;
	size_t _currentNode = 0;
};
