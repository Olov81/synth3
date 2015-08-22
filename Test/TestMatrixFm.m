clear classes;
clc;
close all

fs = 44100;
T = 5;
N = fs*T;

seq = MatrixSequencer('Sequencer', fs);
synth = MatrixFm('Matrix', fs, 6);
lfo = Lfo('Freq lfo', fs);
delay = MultiTapDelay('Delay', fs);
delayFilter = TwoPoleFilter('Delay filter');
chorus = Chorus('Chorus', fs);
mixer = Mixer('Mixer', 1);

synth.gateInput.connect(seq.gateOutput);
synth.frequencyInput.connect(lfo.output);
chorus.input.connect(synth.output);
mixer.channels(1).input.connect(chorus.output);
delay.input.connect(mixer.sendOutput);
delayFilter.input.connect(delay.output)
mixer.returnInput.connect(delayFilter.output);
mixer.channels(1).sendLevelInput.set(0.3);

% Set parameters
seq.bpm = 100;
seq.transpose = 0;
% v = [1 0 0 0  1 0 0 1  0 1 1 0  1 0 1 0 ...
%      1 0 0 0  1 0 0 1  0 1 1 0  1 0 1 0 ...
%      1 0 1 0  1 0 1 1  0 1 1 0  1 0 1 0 ...
%      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0];
% n = [2 0 0 0  2 0 0 1  0 0.3 1 0  1 0 1 0 ...
%      2 0 0 0  2 0 0 1  0 0.3 1 0  1 0 1 0 ...
%      1 0 1 0  1 0 0.3 1  0 0.3 1 0  1 0 6 0 ...
%      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0].*0.95;
% p = [0 0 0 0  3 3 3 0  0 0 5 5  0 0 -2 -2 ...
%      0 0 0 0  7 7 7 0  0 0 8 8  7 7 3 3 ...
%      0 0 7 7  12 12 0 -2  -2 -2 -5 -5  2 2 0 0 ...
%      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0];
v = [1 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0];
n = [64 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]*0.99;
p = [0 0 0 0  3 3 3 0  0 0 5 5  0 0 -2 -2 ...
     0 0 0 0  7 7 7 0  0 0 8 8  7 7 3 3 ...
     0 0 7 7  12 12 0 -2  -2 -2 -5 -5  2 2 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]; 
pattern(1,:) =  [p p] + 12;
pattern(2,:) =  [v v];
pattern(3,:) =  [n n];
seq.pattern = pattern;

synth.envelopes{1}.attackInput.set(1e-3);
synth.envelopes{1}.decayInput.set(6.3);
synth.envelopes{1}.releaseInput.set(0.03);

synth.envelopes{2}.attackInput.set(1e-3);
synth.envelopes{2}.decayInput.set(6.5);
synth.envelopes{2}.releaseInput.set(0.03);

synth.envelopes{3}.attackInput.set(1e-3);
synth.envelopes{3}.decayInput.set(6.3);
synth.envelopes{3}.releaseInput.set(0.03);

synth.envelopes{4}.attackInput.set(1e-3);
synth.envelopes{4}.decayInput.set(6.5);
synth.envelopes{4}.releaseInput.set(0.03);

synth.envelopes{5}.attackInput.set(1e-3);
synth.envelopes{5}.decayInput.set(0.5);
synth.envelopes{5}.releaseInput.set(0.03);

synth.envelopes{6}.attackInput.set(1e-3);
synth.envelopes{6}.decayInput.set(4.3);
synth.envelopes{6}.releaseInput.set(0.03);

scale = 1.5;
synth.ratios(1) = 1 + (1.0011 - 1)*scale;
synth.ratios(2) = 1 + (0.9989 - 1)*scale;
synth.ratios(3) = 1 + (1.0000 - 1)*scale;
synth.ratios(4) = 1 + (1.0000 - 1)*scale;
synth.ratios(5) = 1 + (14.0000 - 1)*scale;
synth.ratios(6) = 1 + (1.0005 - 1)*scale;

scale = 1;
synth.matrix(1,1) = 18*scale;
synth.matrix(1,2) = 0*26*scale;
synth.matrix(7,2) = 58*scale;
synth.matrix(3,4) = 40*scale;
synth.matrix(7,4) = 0*49*scale;
synth.matrix(5,6) = 10*scale;
synth.matrix(7,6) = 0*49*scale;

synth.matrix(2,2) = 500*scale;
synth.ratios(2) = 1*scale;
synth.envelopes{2}.sustainInput.set(1.0);
synth.envelopes{2}.releaseInput.set(1e-3);
synth.envelopes{2}.attackInput.set(1e-4);
lfo.offset = 2000;
lfo.amplitudeInput.set(1900);
lfo.frequencyInput.set(1);

chorus.amplitude = 200;
chorus.bypass = true;

delay.wetmixInput.set(1);
delay.tap1Delay = noteLengthToSamples2(2/16, seq.bpm, fs);
delay.tap2Delay = noteLengthToSamples2(1/16, seq.bpm, fs);
delay.bypass = true;

delayFilter.type = 'bandpass';
delayFilter.frequencyInput.set(2*500/fs);
delayFilter.resonanceInput.set(0.3);

mixer.update(N);