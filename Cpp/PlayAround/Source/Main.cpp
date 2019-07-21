#include "WaveWriter.h"
#include "WaveformGenerator.h"
#include "Framework/ModuleRunner.h"
#include "Lfo.h"
#include "Gain.h"

int main()
{
	static const double fs = 44100;

	WaveWriter writer("Apa.wav");
	
	WaveformGenerator generator;
	
	Gain gain;
	gain.GetGainInput()->Set(0.5);

	Lfo lfo(fs);
	lfo.GetFrequencyInput()->Set(0.4);
	lfo.GetAmplitudeInput()->Set(200);
	lfo.GetOffsetInput()->Set(220);

	generator.GetFrequencyInput()->Connect(lfo.GetOutput());
	gain.GetInput()->Connect(generator.GetOutput());
	writer.GetInput()->Connect(gain.GetOutput());

	ModuleRunner runner(&writer);
	runner.Run(5*static_cast<int>(fs));
	writer.Close();
}
