clear classes;
clc;
close all;

fs = 44100;
T = 20;
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
delayFilter = TwoPoleFilter('Delay filter');
delayMix = Sum('Delay mix', 2);
delayGain = Gain('Delay gain');
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
delayFilter.input.connect( delayfx.output );
delayGain.input.connect( delayFilter.output );
delayMix.inputPorts(1).connect( chorus.output );
delayMix.inputPorts(2).connect( delayGain.output );
reverb.input.connect( delayMix.output );
compressor.input.connect( reverb.output );
writer.input.connect( reverb.output );

% Set parameters
seq.bpm = 125;
seq.transpose = -7;
seq.shuffle = 0.2;
v = [1 2 1 2  1 2 1 2  2 2 1 2  1 2 2 2]/2;
v = [v v v v];
n = [1 1 1 1  1 1 1 1  1 1 1 1  1 1 1 1 ...
     1 1 1 1  1 1 1 1  1 1 1 1  1 1 1 1 ...
     1 1 1 1  1 1 1 1  1 1 1 1  1 1 1 1 ...
     1 1 1 1  1 1 1 1  1 1 1 1  1 1 1 1].*0.95;
p = [0 3 0 3  0 3 0 3  5 10 0 10  0 10 2 3 ...
     0 3 0 3  0 3 0 3  5 10 0 10  0 10 2 3 ...
     0 3 0 3  0 3 0 3  5 10 0 10  0 10 2 3 ...
     0 3 0 3  0 3 0 3  5 10 0 10  0 10 2 3];
p1 = p;
p2 = p;
p2(find(p2==0)) = -4;
pattern(1,:) =  [p1 p2];
pattern(2,:) =  [v v];
pattern(3,:) =  [n n];
seq.pattern = pattern;

porta.frequencyInput.set( 2e-3 );
porta.resonanceInput.set( 1.0 );
porta.bypass = true;

synth.vco1.detune = 0.6;
synth.vco1.voices = 4;
synth.vco1.stereospread = 0.5;
synth.vco1VolumeInput.set(1);

synth.vco2.detune = 0.15;
synth.vco2.voices = 0;
synth.vco2.stereospread = 1.0;
synth.vco2.tuning = 12;
synth.vco2VolumeInput.set(1.0);

synth.noiseAmp.gainInput.set(0.15);
synth.noiseFilter.type = 'bandpass';
synth.noiseFilter.frequencyInput.set(0.1);
synth.noiseGenerator.stereo = true;

synth.cutoffInput.set( 0.1 );
% synth.cutoffInput.connect( filterModulation.output );
synth.resonanceInput.set( 0.5 );
synth.fenv.decayInput.set( 0.02 );
synth.fenv.sustainInput.set( 0.0 );
synth.fenv.attackInput.set( 0.001 );
synth.fenv.releaseInput.set( 0.02 );
synth.fenvAmount.gainInput.set( 0.3 );

synth.aenv.decayInput.set( 0.1 );
synth.aenv.releaseInput.set( 0.02 );
synth.aenv.attackInput.set( 1e-2 );
synth.aenv.sustainInput.set( 0.0 );

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

delayfx.wetmixInput.set( 1 );
delayfx.tap1Delay = noteLengthToSamples2(1/4, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/4, seq.bpm, fs);
delayfx.feedback = 0.4;
delayfx.bypass = false;
delayGain.gainInput.set( 0.3 );
delayFilter.type = 'bandpass';
delayFilter.frequencyInput.set(0.001);

reverb.time = 2;
reverb.mix = 0.005;
reverb.initialDelay = 0.1;
reverb.bypass = true;

tic
writer.update(N);
toc

% player.update(N);