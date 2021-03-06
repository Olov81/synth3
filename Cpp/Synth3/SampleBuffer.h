#pragma once

class SampleBuffer
{
public:

	SampleBuffer(const double* pBuffer, unsigned int bufferLength);

	double GetNextSample();

	void SetLoopEnabled(bool enabled);

	void SetLoopInterval(unsigned int start, unsigned int end);

private:

	double GetNextSampleLoopEnabled();

	double GetNextSampleLoopDisabled();

	typedef double (SampleBuffer::*DoGetNextSample)();

	DoGetNextSample _getNextSample;

	const double* _pBuffer;

	unsigned int _bufferLength;

	unsigned int _currentPosition;

	unsigned int _loopStart;

	unsigned int _loopEnd;

};
