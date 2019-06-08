#include "Interpolator.h"
#include "ISampleProvider.h"
#include <vector>
#include "TestUtils/Assert.h"
#include "TestUtils/SignalSource.h"

class SampleProvider : public ISampleProvider
{
public:

	SampleProvider(std::initializer_list<double> samples)
		:_samples(samples.begin())
	{
	}

	double GetNextSample() override
	{
		const auto sample = *_samples;
		_samples++;
		return sample;
	}

private:

	std::initializer_list<double>::const_iterator _samples;
};

TEST(InterpolatorTests)
{
	SampleProvider sampleProvider({ 1.0, 3.0, 2.0 });
	Interpolator interpolator(&sampleProvider);

	ASSERT_EQUAL(0.5, interpolator.GetNextSample(0.5));
	ASSERT_EQUAL(0.6, interpolator.GetNextSample(0.1));
	ASSERT_EQUAL(2.5, interpolator.GetNextSample(1.9));
	ASSERT_EQUAL(2.0, interpolator.GetNextSample(0.5));
}
