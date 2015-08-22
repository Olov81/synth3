
clear classes;
clc;
close all;
fs = 44100;
T = 2.0;
N = T*fs;

fs = 44100;
osc = SineWaveOscillator('Osc', fs);
beatOsc = PulseGenerator('Beat osc', fs, 138, 50);
penv = EnvelopeGenerator('Penv', fs);
penvAmount = Gain('Penv amount', 300);

writer = WaveWriter('Writer');


writer.input.connect(osc.output);
penvAmount.input.connect(penv.output);
osc.frequencyInput.connect(penvAmount.output);
penv.gateInput.connect(beatOsc.output);
osc.gateInput.connect(beatOsc.output);
osc.phaseoffset = pi/4;
penv.attackInput.set(1e-3);
penv.decayInput.set(0.05);
penv.sustainInput.set(0.1);

writer.update(N);
sound(0.2*writer.y, fs);