#include "../SamplePlayer.h"
#include "../TestUtils/Assert.h"
#include "../TestUtils/SignalSource.h"
#include "../TestUtils/SignalSink.h"
#include "Framework/ModuleRunner.h"

class FilterStub : public IFilter
{
public:

	virtual void SetCutoffFrequency(double frequency) override
	{
		SetFrequencies.push_back(frequency);
	}

	virtual double Update(double input) override
	{
		return -input;
	}

	std::vector<double> SetFrequencies;
};

TEST(SamplePlayerTests)
{
	const double sampleBuffer[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };

	FilterStub filter;
	SamplePlayer player(sampleBuffer, sizeof(sampleBuffer) / sizeof(double), &filter);
	SignalSource decimationSource({ 2.0, 2.0, 0.5, 1.0 });
	SignalSink signalSink;

	player.GetDecimationInput()->Connect(decimationSource.GetOutput());
	signalSink.GetInput()->Connect(player.GetOutput());

	ModuleRunner runner(&signalSink);

	runner.Run(4);

	ASSERT_EQUAL(-2.0, signalSink.GetSample(0));
	ASSERT_EQUAL(-4.0, signalSink.GetSample(1));
	ASSERT_EQUAL(-4.5, signalSink.GetSample(2));
	ASSERT_EQUAL(-5.5, signalSink.GetSample(3));
	Assert(filter.SetFrequencies).AreAllEqualTo({ 0.5, 0.5, 2.0, 1.0 });
}
