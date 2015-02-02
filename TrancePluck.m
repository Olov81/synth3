clear classes;
clc;
close all;

fs = 44100;
T = 33;
t = (0:T*fs-1)/fs;
N = length(t);


% Create modules
seq = MatrixSequencer('Sequencer', fs);
porta = TwoPoleFilter('Portamento');
vibrato = Lfo('Vibrato', fs);
synth = MonoSynth('Synth', fs);
filter = TwoPoleFilter('Filter');
sampleAndHold = SampleAndHold('SampleAndHold');
filterModulation = CustomEnvelope('FilterModulation', fs);
chorus = Chorus('Chorus', fs);
compressor = Compressor('Compressor', fs);
delayfx = MultiTapDelay('Delay', fs);
reverb = Reverb('Reverb', fs);
reverbHpf = TwoPoleFilter('Reverb hpf');
writer = WaveWriter('Writer');

% Connect everything up
porta.input.connect( seq.cvOutput );
synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( porta.output );
filter.input.connect( synth.output );
filter.frequencyInput.connect( filterModulation.output );
sampleAndHold.input.connect( filter.output );
chorus.input.connect( sampleAndHold.output );
delayfx.input.connect( chorus.output );
reverb.input.connect( delayfx.output );
reverbHpf.input.connect( reverb.output );
compressor.input.connect( reverbHpf.output );
writer.input.connect( compressor.output );

% Set parameters
seq.bpm = 138;
seq.transpose = 2;
v1 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0]*1;
n1 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0]/1.4;
 
v2 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
      1 0 0 1 0 0 1 0 1 0 0 0 1 0 1 0 ...
      1 0 0.7 1 0 0 1 0 1 0 0 1 0 0 1 0]*1;
n2 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
     1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
     1 0 0 1 0 0 1 0 1 0 0 0 1 0 1 0 ...
     1 0 1 1 0 0 1 0 1 0 0 1 0 0 1 0]/1.4;
 
p11 = [[3 3 3 -5 -5 -5 -2 -2 3 3 3 -5 -5 -5 -2 -2] ...
      [2 2 2 -7 -7 -7 -2 -2 2 2 2 -7 -7 -7 -2 -2] ...
      [0 0 0 -7 -7 -7 -2 -2 0 0 0 -7 -7 -7 -2 -2] ...
      [0 0 0 -7 -7 -7 -2 -2 0 0 0 -7 -7 -7 -2 -2]];

p12 = [[3 3 3 -5 -5 -5 -2 -2 3 3 3 -5 -5 -5 -2 -2] ...
      [2 2 2 -7 -7 -7 -2 -2 2 2 2 -7 -7 -7 -2 -2] ...
      [0 0 0 -7 -7 -7 -2 -2 0 0 0 0 2 2 -2 -2] ...
      [-5 -5 -2 -5 -5 -5 -2 -2 2 2 2 -5 -5 -5 -2 -2]];
pattern(1,:) =  [p11 p12 p11 p12];
pattern(2,:) =  [v1 v2 v1 v2];
pattern(3,:) =  [n1 n2 n1 n2];
seq.pattern = pattern;

porta.frequencyInput.set( 2e-3 );
porta.resonanceInput.set( 1.0 );
porta.bypass = true;

synth.vco1.detune = 0.55;
synth.vco1.voices = 8;
synth.vco1.stereospread = 0.8;
synth.vco1VolumeInput.set(1);

synth.vco2.detune = 0.3;
synth.vco2.voices = 0;
synth.vco2.stereospread = 1.0;
synth.vco2.tuning = 12;
synth.vco2VolumeInput.set(1.0);

synth.noiseAmp.gainInput.set(1);
synth.noiseFilter.type = 'highpass';
synth.noiseFilter.frequencyInput.set(0.15);
synth.noiseGenerator.stereo = true;

synth.cutoffInput.set( 0.005 );
synth.cutoffInput.connect( filterModulation.output );
synth.resonanceInput.set( 0.3 );
synth.fenv.decayInput.set( 0.03 );
synth.fenv.sustainInput.set( 0.0 );
synth.fenv.attackInput.set( 0.0001 );
synth.fenv.releaseInput.set( 0.1 );
synth.fenvAmount.gainInput.set( 0.15 );

synth.aenv.decayInput.set( 0.1 );
synth.aenv.releaseInput.set( 0.15 );
synth.aenv.attackInput.set( 1e-2 );
synth.aenv.sustainInput.set( 1 );

synth.penv.decayInput.set( 0.0015 );
synth.penv.releaseInput.set( 0.1 );
synth.penv.attackInput.set( 2e-3 );
synth.penv.sustainInput.set( 0 );
synth.penvAmount.gainInput.set( 500.0 );

p1.time = 0;
p1.value = 2*20/fs;
p2.time = 23;
p2.value = 2*10000/fs;
p3.time = 25;
p3.value = 2*100/fs;
filterModulation.points = [p1 p2 p3];
filter.type = 'highpass';
filter.resonanceInput.set( 0.1 );
filter.bypass = true;

sampleAndHold.decimationInput.set(12000/fs);
sampleAndHold.mix = 0.5;

chorus.mix = 0.35;
chorus.frequency = 2;
chorus.bypass = true;
chorus.rightDelay = 0.03*fs;
chorus.leftDelay = 0.05*fs;

compressor.ratio = 0.5;
compressor.threshold = 0.5;
compressor.attack = 0.01;
compressor.release = 0.5;
compressor.bypass = false;

delayfx.wetmixInput.set( 0.4 );
delayfx.tap1Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/16, seq.bpm, fs);
delayfx.feedback = 0.5;
delayfx.bypass = false;

reverb.time = 6;
reverb.mix = 0.004;
reverb.initialDelay = 0.1;
reverb.bypass = false;
reverb.hfFallOffRate = 0.999;
reverb.width = 1.0;

reverbHpf.type = 'highpass';
reverbHpf.resonanceInput.set( 0.9 );
reverbHpf.frequencyInput.set( 0.015 );

tic
writer.update(N);
toc

% player.update(N);