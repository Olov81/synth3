clear;
close all;

fs = 44100;
bpm = 138;
hold = 0.5;
T = 5;

sidechainGain = SidechainGain('Sidechain', fs, bpm, hold);
wavWriter = WaveWriter('Writer');

wavWriter.input.connect(sidechainGain.output);

wavWriter.update(T*fs);

plot(wavWriter.y);
