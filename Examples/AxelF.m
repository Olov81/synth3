clear classes;
clc;
close all;
% addpath('../Functions');
% addpath('../Framework');
% addpath('../Modules');

fs = 44100;
T = 10;
t = (0:T*fs-1)/fs;
N = length(t);


% Create modules
seq = MatrixSequencer('Sequencer', fs);
porta = TwoPoleFilter('Portamento');
vibrato = Lfo('Vibrato', fs);
synth = MonoSynth('Synth', fs);
filter = TwoPoleFilter('Filter');
filterModulation = CustomEnvelope('FilterModulation', fs);
chorus = Chorus('Chorus', fs);
compressor = Compressor('Compressor', fs);
delayfx = MultiTapDelay('Delay', fs);
reverb = Reverb('Reverb', fs);
writer = WaveWriter('Writer');

% Connect everything up
porta.input.connect( seq.cvOutput );
synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( porta.output );
filter.input.connect( synth.output );
filter.frequencyInput.connect( filterModulation.output );
chorus.input.connect( filter.output );
delayfx.input.connect( chorus.output );
reverb.input.connect( delayfx.output );
compressor.input.connect( reverb.output );
writer.input.connect( reverb.output );

% Set parameters
seq.bpm = 117;
seq.transpose = -4;
seq.loop = true;
v = [1 0 0 0  1 0 0 1  0 1 1 0  1 0 1 0 ...
     1 0 0 0  1 0 0 1  0 1 1 0  1 0 1 0 ...
     1 0 1 0  1 0 1 1  0 1 1 0  1 0 1 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0];
n = [2 0 0 0  2 0 0 1.5  0 0.3 1 0  1 0 1 0 ...
     2 0 0 0  2 0 0 1.5  0 0.3 1 0  1 0 1 0 ...
     1 0 1 0  1 0 0.3 1  0 0.3 1 0  1 0 6 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0].*0.95;
p = [0 0 0 0  3 3 3 0  0 0 5 5  0 0 -2 -2 ...
     0 0 0 0  7 7 7 0  0 0 8 8  7 7 3 3 ...
     0 0 7 7  12 12 0 -2  -2 -2 -5 -5  2 2 0 0 ...
     0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]; 
pattern(1,:) =  p;
pattern(2,:) =  v;
pattern(3,:) =  n;
seq.pattern = pattern;

porta.frequencyInput.set( 2e-3 );
porta.resonanceInput.set( 1.0 );
porta.bypass = true;

synth.vco1.waveform = 'squarewave';
synth.vco1.detune = 0.1;
synth.vco1.voices = 2;
synth.vco1.stereospread = 0.1;
synth.vco1VolumeInput.set(0.5);

synth.vco2.waveform = 'sawtooth';
synth.vco2.detune = 0.15;
synth.vco2.voices = 4;
synth.vco2.stereospread = 1.0;
synth.vco2.tuning = 12;
synth.vco2VolumeInput.set(0.4);

synth.noiseAmp.gainInput.set(0*0.15);
synth.noiseFilter.type = 'bandpass';
synth.noiseFilter.frequencyInput.set(0.1);
synth.noiseGenerator.stereo = true;

synth.cutoffInput.set( 0.1 );
% synth.cutoffInput.connect( filterModulation.output );
synth.resonanceInput.set( 0.1 );
synth.fenv.decayInput.set( 0.2 );
synth.fenv.sustainInput.set( 0.2 );
synth.fenv.attackInput.set( 0.005 );
synth.fenv.releaseInput.set( 0.002 );
synth.fenvAmount.gainInput.set( 0.5 );

synth.aenv.decayInput.set( 0.04 );
synth.aenv.releaseInput.set( 0.05 );
synth.aenv.attackInput.set( 1e-2 );
synth.aenv.sustainInput.set( 1 );

synth.flfo.amplitudeInput.set(1.0);
synth.flfo.frequencyInput.set(8);


p1.time = 0;
p1.value = 2*100/fs;
p2.time = 7;
p2.value = 2*5000/fs;
p3.time = 15;
p3.value = 2*100/fs;
filterModulation.points = [p1 p2 p3];
filter.type = 'highpass';
filter.resonanceInput.set( 0.1 );
filter.bypass = true;

chorus.mix = 0.35;
chorus.frequency = 2;
chorus.bypass = true;
chorus.rightDelay = 0.03*fs;
chorus.leftDelay = 0.05*fs;

compressor.ratio = 0.5;
compressor.threshold = 0.2;
compressor.attack = 0.02;
compressor.release = 0.2;
compressor.bypass = true;

delayfx.wetmixInput.set( 0.18 );
delayfx.tap1Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.tap2Delay = 200; %noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.feedback = 0.2;
delayfx.bypass = false;

reverb.time = 2;
reverb.mix = 0.005;
reverb.initialDelay = 0.1;
reverb.bypass = true;

tic
writer.update(N);
toc

% player.update(N);