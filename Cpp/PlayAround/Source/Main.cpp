#include "WaveWriter.h"
#include "WaveformGenerator.h"
#include "Framework/ModuleRunner.h"
#include "Constant.h"

int main()
{
	WaveWriter writer("Apa.wav");
	WaveformGenerator generator;
	Constant constant(220);

	generator.GetFrequencyInput()->Connect(constant.GetOutput());
	writer.GetInput()->Connect(generator.GetOutput());

	ModuleRunner runner(&writer);
	runner.Run(44100);
	writer.Close();
}
