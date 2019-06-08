clear classes;
clc;
close all;

fs = 44100;
T = 60;
t = (0:T*fs-1)/fs;
N = length(t);


% Create modules
seq = MatrixSequencer('Sequencer', fs);
mixer = Mixer('Main mixer', 1);
mixer2 = Mixer('Mixer 2', 1);
porta = TwoPoleFilter('Portamento');
vibrato = Lfo('Vibrato', fs);
synth = MonoSynth('Synth', fs);
cleanupFilter = TwoPoleFilter('Cleanup filter');
sampleAndHold = SampleAndHold('SampleAndHold');
filterModulation = CustomEnvelope('FilterModulation', fs);
compressor = Compressor('Compressor', fs);
delayfx = MultiTapDelay('Delay', fs);
delayFilter = TwoPoleFilter('Delay filter');
delayCompressor = Compressor('Delay compressor', fs);
reverb = Reverb('Reverb', fs);
reverbHpf = TwoPoleFilter('Reverb hpf');
writer = WaveWriter('Writer');

% Connect everything up
porta.input.connect( seq.cvOutput );
synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( porta.output );
% filter.frequencyInput.connect( filterModulation.output );
cleanupFilter.input.connect( synth.output );
sampleAndHold.input.connect( cleanupFilter.output );
mixer.channels(1).input.connect(sampleAndHold.output);
delayCompressor.sidechainInput.connect( mixer.sendOutput );
delayfx.input.connect( mixer.sendOutput );
delayFilter.input.connect( delayfx.output );
delayCompressor.input.connect( delayFilter.output );
mixer.returnInput.connect(delayCompressor.output);
mixer2.channels(1).input.connect( mixer.mainOutput );
reverb.input.connect( mixer2.sendOutput );
reverbHpf.input.connect( reverb.output );
mixer2.returnInput.connect( reverbHpf.output );
compressor.input.connect( mixer2.mainOutput );
writer.input.connect( compressor.output );

% Set parameters
seq.bpm = 138;
seq.transpose = -6;
v1 = [0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1 ... 
      0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1 ...
      0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1 ... 
      0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1]*1;
  
n1 = [0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1 ... 
      0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1 ...
      0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1 ... 
      0 0 1 0  1 1 0 1  0 0 1 0  1 1 0 1]/1.1;
   
p1 = [10 10 10 10  10 10 10 8  8 8 8 8  8 8 8 7 ...
       7 7 7 7  7 7 7 3  3 3 3 3  3 3 3 10 ...
       10 10 10 10  10 10 10 8  8 8 8 8  8 8 8 7 ...
       7 7 7 7  7 7 7 3  3 3 3 3  3 3 3 8 ];
  
p2 = [8 8 8 8  8 8 8 7  7 7 7 7  7 7 7 3 ...
       3 3 3 3  3 3 3 0  0 0 0 0  0 0 0 8 ...
       8 8 8 8  8 8 8 7  7 7 7 7  7 7 7 3 ...
       3 3 3 3  3 3 3 0  0 0 0 0  0 0 0 10 ];

p3 = [10 10 10 10  10 10 10 12  12 12 12 12  12 12 12 8 ...
       8 8 8 8  8 8 8 3  3 3 3 3  3 3 3 10 ...
       10 10 10 10  10 10 10 12  12 12 12 12  12 12 12 8 ...
       8 8 8 8  8 8 8 15  15 15 15 15  14 14 14 10 ];
  
p4 = [10 10 10 10  10 10 10 5  5 5 5 5  5 5 5 3 ...
       3 3 3 3  3 3 3 2  2 2 2 2  2 2 2 10 ...
       10 10 10 10  10 10 10 5  5 5 5 5  5 5 5 3 ...
       3 3 3 3  3 3 3 2  2 2 2 2  2 2 2 10 ];
   
pattern(1,:) =  [p1 p2 p3 p4 p1 p2 p3 p4];
pattern(2,:) =  [v1 v1 v1 v1 v1 v1 v1 v1];
pattern(3,:) =  [n1 n1 n1 n1 n1 n1 n1 n1];
seq.pattern = pattern;

porta.frequencyInput.set( 1e-6 );
porta.resonanceInput.set( 1.0 );
porta.bypass = true;

synth.vco1.detune = 0.5;
synth.vco1.voices = 8;
synth.vco1.stereospread = 0.8;
synth.vco1VolumeInput.set(0.1);

synth.vco2.detune = 0.4;
synth.vco2.voices = 0;
synth.vco2.stereospread = 0.4;
synth.vco2.tuning = 11.95;
synth.vco2VolumeInput.set(1.0);

synth.noiseAmp.gainInput.set(0.1);
synth.noiseFilter.type = 'bandpass';
synth.noiseFilter.frequencyInput.set(0.2);
synth.noiseGenerator.stereo = true;

% synth.cutoffInput.set( 2*20/fs );
synth.cutoffInput.connect( filterModulation.output );
synth.resonanceInput.set( 0.1 );
synth.fenv.decayInput.set( 0.17 );
synth.fenv.sustainInput.set( 0.0005);
synth.fenv.attackInput.set( 0.001 );
synth.fenv.releaseInput.set( 0.02 );
synth.fenvAmount.gainInput.set( 0.12 );

synth.aenv.decayInput.set( 0.15 );
synth.aenv.releaseInput.set( 0.2 );
synth.aenv.attackInput.set( 5e-3 );
synth.aenv.sustainInput.set( 1.0 );

synth.penv.decayInput.set( 0.01 );
synth.penv.releaseInput.set( 0.15 );
synth.penv.attackInput.set( 2e-3 );
synth.penv.sustainInput.set( 0 );
synth.penvAmount.gainInput.set( 0*1.0 );

synth.flfo.amplitudeInput.set( 0*50 );
synth.flfo.frequencyInput.set( 4 );

synth.portaRateInput.set( 0.1 );

p1.time = 0;
p1.value = 2*20/fs;
p2.time = 15;
p2.value = 2*10000/fs;
p3.time = 20;
p3.value = 2*10000/fs;
p4.time = 25;
p4.value = 2*100/fs;
p5.time = 28;
p5.value = 2*10000/fs;
p6.time = 40;
p6.value = 2*10000/fs;
p7.time = 55;
p7.value = 2*40/fs;

filterModulation.points = [p1 p2 p3 p4 p5 p6 p7];


cleanupFilter.type = 'highpass';
cleanupFilter.resonanceInput.set( 0.5 );
cleanupFilter.frequencyInput.set( 0.003 );
cleanupFilter.bypass = false;

sampleAndHold.decimationInput.set(8000/fs);
sampleAndHold.mix = 0.1;
sampleAndHold.bypass = true;

compressor.ratio = 0.2;
compressor.threshold = 0.5;
compressor.attack = 0.02;
compressor.release = 0.2;
compressor.bypass = true;

delayfx.wetmixInput.set( 1.0 );
delayfx.tap1Delay = noteLengthToSamples2(3/16, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/16, seq.bpm, fs);
delayfx.feedback = 0.5;
delayfx.bypass = false;

delayFilter.type = 'bandpass';
delayFilter.frequencyInput.set( 2*400/fs );
delayFilter.resonanceInput.set( 0.2 );

delayCompressor.useSidechainInput = true;
delayCompressor.ratio = 0.01;
delayCompressor.threshold = 0.7;
delayCompressor.attack = 0.001;
delayCompressor.release = 0.3;

mixer.channels(1).sendLevelInput.set( 0.4 );
mixer.channels(1).levelInput.set( 1.0 );

mixer.channels(1).highShelfEq.bypass = true;
mixer.channels(1).highShelfEq.gainInput.set( 2.5 );
mixer.channels(1).highShelfEq.frequencyInput.set( 2*6000/fs );

mixer.channels(1).lowShelfEq.bypass = true;
mixer.channels(1).lowShelfEq.gainInput.set( 0.5 );
mixer.channels(1).lowShelfEq.frequencyInput.set( 2*800/fs );

mixer.channels(1).paramEq1.bypass = true;
mixer.channels(1).paramEq1.frequencyInput.set(2*1500/fs);
mixer.channels(1).paramEq1.gainInput.set( 0.5 );
mixer.channels(1).paramEq1.qInput.set( 0.1 );

mixer.channels(1).paramEq2.bypass = true;
mixer.channels(1).paramEq2.frequencyInput.set(2*300/fs);
mixer.channels(1).paramEq2.gainInput.set( 2 );
mixer.channels(1).paramEq2.qInput.set( 0.4 );

mixer2.channels(1).sendLevelInput.set( 0.004 );
mixer2.channels(1).highShelfEq.bypass = true;
mixer2.channels(1).highShelfEq.gainInput.set( 2.0 );
mixer2.channels(1).highShelfEq.frequencyInput.set( 2*5000/fs );

reverb.time = 6;
reverb.mix = 1.0;
reverb.initialDelay = 0.1;
reverb.bypass = false;
reverb.hfFallOffRate = 0.999;
reverb.width = 1.0;

reverbHpf.type = 'highpass';
reverbHpf.resonanceInput.set( 0.9 );
reverbHpf.frequencyInput.set( 0.02 );

tic
writer.update(N);
toc

% player.update(N);