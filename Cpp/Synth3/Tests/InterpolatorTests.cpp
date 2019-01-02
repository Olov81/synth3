#include "InterpolatorTests.h"
#include "../Interpolator.h"
#include <vector>
#include "Assert.h"

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

void InterpolatorTests()
{
	SampleProvider sampleProvider({ 1.0, 3.0, 2.0 });

	Interpolator interpolator(&sampleProvider);

	AssertEqual(0.5, interpolator.GetNextSample(0.5));
	AssertEqual(0.6, interpolator.GetNextSample(0.1));
	AssertEqual(2.5, interpolator.GetNextSample(1.9));
	AssertEqual(2.0, interpolator.GetNextSample(0.5));
}
