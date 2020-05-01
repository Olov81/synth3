#pragma once

class IWaveformGenerator
{
public:

	virtual ~IWaveformGenerator() = default;

	virtual double Update(const double& frequency) = 0;

	virtual void ResetPhase(const double& relativeTimeInstant) = 0;
};