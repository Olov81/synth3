clear classes;
clc;
close all;

fs = 44100;
T = 20;
t = (0:T*fs-1)/fs;
N = length(t);

seq = MatrixSequencer('Sequencer', fs);
seq.bpm = 120;
seq.transpose = -30;
% pattern = seq.pattern;

% v1 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ... 
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0]*1;
% n1 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0]/1.01;
% p1 = [2 2 0 0 3 3 3 0 0 0 3 3 3 10 3 3 ...
%       8 8 7 7 3 3 3 0 0 0 3 3 3 0 7 7 ...
%       5 5 2 2 5 5 5 2 2 2 5 5 5 7 5 5 ...
%       15 15 14 14 5 5 5 2 2 2 5 5 5 5 10 10 ];
%   
% v2 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 1 1 1 0]*1;
% n2 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
%       1 0 1 0 1 0 0 1 0 0 1 0 1 1 1 0]/1.01;
% p2 = [7 7 0 0 5 5 5 0 0 0 5 5 5 10 5 5 ...
%       15 15 8 8 10 10 10 8 8 8 10 10 10 3 5 5 ...
%       5 5 3 3 5 5 5 3 3 3 5 5 5 3 5 5 ...
%       10 10 5 5 3 3 3 2 2 2 3 3 0 3 5 5 ];
  

v1 = [1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0];
n1 = [1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0]*1.9;
p1 = [7 7 7 0  0 0 7 7  7 0 0 0  7 7 0 0];

p12 = [7 7 7 0  0 0 7 7  7 0 0 0  7 7 0 0] - 12 + 3;
p13 = [[7 7 7 0  0 0]+3 [7 7  7 0 0 0  10 10 9 9] + 5];

v2 = [0 1 1 0  1 1 0 1  1 0 1 1  0 1 0 1]*0.3;
n2 = [0 1 1 0  1 1 0 1  1 0 1 1  0 1 0 1]*0.2;
p2 = [12 0 12 12  0 12 12 0  0 0 12 0  0 0 0 12] - 12;

p = [p1 p12 p1 p13];
v = [v1 v1 v1 v1];
n = [n1 n1 n1 n1].*0.99;

pattern(1,:) =  [p p p p];
pattern(2,:) =  [v v v v];
pattern(3,:) =  [n n n n];

% pattern{2}.velocity =   [v2 v2 v2 v2 vend];
% pattern{2}.notelength = [n2 n2 n2 n2 vend].*0.99;
% pattern{2}.pitch =      [p2 p2 p2 p2 vend] + transpose;

% pattern(1,:) = [p1 p2 p1 p2];
% pattern(2,:) = [v1 v2 v1 v2];
% pattern(3,:) = [n1 n2 n1 n2];

seq.pattern = pattern;

lfo = Lfo('LFO', fs);
lfo.amplitudeInput.set( 0.01 );
lfo.frequencyInput.set( 20 );
lfo.offset = 1;

lfo2 = Lfo('LFO 2', fs);
lfo2.amplitudeInput.set( 0.01 );
lfo2.frequencyInput.set( 0.5 );
lfo2.offset = 0.01;

synth = MonoSynth('Synth', fs);
hpFilter = TwoPoleFilter('High pass filter');
bitCrusher = SampleAndHold('Bit crusher');
delayfx = MultiTapDelay('Delay', fs);
writer = WaveWriter('Writer');

cv = Multiply('CV', 2);
cv.inputPorts(1).connect( seq.cvOutput );
cv.inputPorts(2).connect( lfo.output );

synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( cv.output );
hpFilter.input.connect( synth.output );
bitCrusher.input.connect( hpFilter.output );
delayfx.input.connect( bitCrusher.output );

synth.vco1.detune = 0.1;
synth.vco1.voices = 1;
synth.vco1.stereospread = 0.7;
synth.vco2.detune = 0.2;
synth.vco2.voices = 0;
synth.vco2.stereospread = 1.0;
synth.vco2.tuning = 12;
synth.noiseAmp.gainInput.set(0.0);
synth.noiseFilter.type = 'highpass';
synth.noiseFilter.frequencyInput.set(0.4);
synth.noiseGenerator.stereo = true;

synth.fenv.decayInput.set( 0.2 );
synth.fenv.sustainInput.set( 0.5 );
synth.fenv.attackInput.set( 0.2 );
synth.fenv.releaseInput.set( 0.05 );

synth.aenv.decayInput.set( 0.04 );
synth.aenv.releaseInput.set( 0.03 );
synth.aenv.attackInput.set( 1e-3 );
synth.aenv.sustainInput.set( 1 );

synth.penv.rate = 0.3;
synth.penv.attackInput.set( 1e-5 );
synth.penv.decayInput.set( 0.002 );
synth.penvAmount.gainInput.set(500);
synth.fenvAmount.gainInput.set( 0.01 );
synth.resonanceInput.set( 0.8 );

% synth.fenvAmount.gainInput.connect(lfo2.output);
synth.cutoffInput.connect(lfo2.output);
% synth.cutoffInput.set( 0.005 );

% synth.cutoffInput.set( 0.01 );

hpFilter.type = 'highpass';
hpFilter.frequencyInput.set(0.002);
% hpFilter.bypass = true;
% hpFilter.frequencyInput.connect(lfo2.output);

bitCrusher.decimationInput.set( 2100/fs );
bitCrusher.bypass = false;

delayfx.wetmixInput.set( 0.1 );
delayfx.tap1Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.bypass = false;

writer.input.connect( delayfx.output );
% writer.input.connect( synth.output );

tic
writer.update(N);
toc

% player.update(N);