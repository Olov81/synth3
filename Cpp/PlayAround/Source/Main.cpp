#include "WaveWriter.h"
#include "WaveformGenerator.h"
#include "Framework/ModuleRunner.h"
#include "Lfo.h"
#include "Gain.h"
#include <chrono>

template<class F>
double MeasureRunTimeInSeconds(const F& f)
{
	const auto begin = std::chrono::steady_clock::now();
	f();
	const auto end = std::chrono::steady_clock::now();

	const auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	return microseconds * 1e-6;
}

int main()
{
	static const double fs = 44100;

	WaveWriter writer("Apa.wav");
	
	WaveformGenerator generator;
	
	Gain gain;
	gain.GetGainInput()->Set(0.5);

	Lfo lfo(fs);
	lfo.GetFrequencyInput()->Set(0.4);
	lfo.GetAmplitudeInput()->Set(800);
	lfo.GetOffsetInput()->Set(1220);

	generator.GetFrequencyInput()->Connect(lfo.GetOutput());
	gain.GetInput()->Connect(generator.GetOutput());
	writer.GetInput()->Connect(gain.GetOutput());

	ModuleRunner runner(&writer);

	auto update = [&]() {runner.Run(5 * static_cast<int>(fs)); };

	auto duration = MeasureRunTimeInSeconds(update);

	writer.Close();

	std::cout << "Time: " << duration << std::endl;
}
