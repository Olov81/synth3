#include "Interpolator.h"
#include "ISampleProvider.h"
#include <vector>
#include "TestUtils/Assert.h"
#include "Framework/ModuleRunner.h"
#include "TestUtils/SignalSource.h"
#include "TestUtils/SignalSink.h"

class SampleProvider : public ISampleProvider
{
public:

	SampleProvider(std::initializer_list<double> samples)
		:_samples(samples.begin())
	{
	}

	virtual double GetNextSample() 
	{
		double sample = *_samples;
		_samples++;
		return sample;
	}

private:

	std::initializer_list<double>::const_iterator _samples;
};

TEST(InterpolatorTests)
{
	SampleProvider sampleProvider({ 1.0, 3.0, 2.0 });
	SignalSource decimation({ 0.5, 0.1, 1.9, 0.5 });
	Interpolator interpolator(&sampleProvider);
	SignalSink sink;

	interpolator.GetDecimationInput()->Connect(decimation.GetOutput());
	sink.GetInput()->Connect(interpolator.GetOutput());

	ModuleRunner runner(&sink);

	runner.Run(4);

	ASSERT_EQUAL(0.5, sink.GetSample(0));
	ASSERT_EQUAL(0.6, sink.GetSample(1));
	ASSERT_EQUAL(2.5, sink.GetSample(2));
	ASSERT_EQUAL(2.0, sink.GetSample(3));
}
