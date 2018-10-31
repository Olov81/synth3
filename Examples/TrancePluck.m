clear classes;
clc;
close all;

fs = 44100;
T = 30;
t = (0:T*fs-1)/fs;
N = length(t);


% Create modules
seq = MatrixSequencer('Sequencer', fs);
mixer = Mixer('Main mixer', 1);
mixer2 = Mixer('Mixer 2', 1);
porta = TwoPoleFilter('Portamento');
vibrato = Lfo('Vibrato', fs);
synth = MonoSynth('Synth', fs);
filter = TwoPoleFilter('Filter');
sampleAndHold = SampleAndHold('SampleAndHold');
filterModulation = CustomEnvelope('FilterModulation', fs);
chorus = Chorus('Chorus', fs);
compressor = Compressor('Compressor', fs);
delayfx = MultiTapDelay('Delay', fs);
delayfx2 = MultiTapDelay('Delay', fs);
delayCompressor = Compressor('Delay compressor', fs);
reverb = Reverb('Reverb', fs);
reverbHpf = TwoPoleFilter('Reverb hpf');
writer = WaveWriter('Writer');

% Connect everything up
porta.input.connect( seq.cvOutput );
synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( porta.output );
filter.input.connect( synth.output );
% filter.frequencyInput.connect( filterModulation.output );
sampleAndHold.input.connect( filter.output );
chorus.input.connect( sampleAndHold.output );
mixer.channels(1).input.connect(chorus.output);
delayCompressor.sidechainInput.connect( mixer.sendOutput );
delayfx.input.connect( mixer.sendOutput );
delayfx2.input.connect( delayfx.output );
delayCompressor.input.connect( delayfx2.output );
mixer.returnInput.connect(delayCompressor.output);
mixer2.channels(1).input.connect( mixer.mainOutput );
reverb.input.connect( mixer2.sendOutput );
reverbHpf.input.connect( reverb.output );
mixer2.returnInput.connect( reverbHpf.output );
compressor.input.connect( mixer2.mainOutput );
writer.input.connect( compressor.output );

% Set parameters
seq.bpm = 138;
seq.transpose = -9;
v1 = [0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 ... 
      0 0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 ...
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ... 
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]*1;

v2 = [0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 ... 
      0 0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 ...
      0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 ... 
      0 0 1 0 0 0 1 0 0 0 1 0 1 0 1 0]*1;
  
v3 = [0 0 0 0  0 0 0 0  1 0 0 0  1 0 1 0 ... 
      0 0 0 0  0 0 1 0  0 0 1 0  1 0 1 0 ...
      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ... 
      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]*1;
  
n1 = [0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 ... 
      0 0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 ...
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ... 
      0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]/1.01;
n2 = [0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 ... 
      0 0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 ...
      0 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 ... 
      0 0 1 0 0 0 1 0 0 0 1 0 1 0 1 0]/1.01;
n3 = [0 0 0 0  0 0 0 0  1 0 0 0  1 0 1 0 ... 
      0 0 0 0  0 0 1 0  0 0 1 0  1 0 1 0 ...
      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0 ... 
      0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]/1.01;
  
% v1 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0]*1;
% n1 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0]/1.4;
%  
% v2 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
%       1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
%       1 0 0 1 0 0 1 0 1 0 0 0 1 0 1 0 ...
%       1 0 0.7 1 0 0 1 0 1 0 0 1 0 0 1 0]*1;
% n2 = [1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ... 
%      1 0 0 1 0 0 1 0 1 0 0 1 0 0 1 0 ...
%      1 0 0 1 0 0 1 0 1 0 0 0 1 0 1 0 ...
%      1 0 1 1 0 0 1 0 1 0 0 1 0 0 1 0]/1.4;
%  
p11 = [[12 12 12 12  12 12 12 12  12 12 12 12  12 12 11 11] ...
       [11 11 11 11  11 11 7 7  7 7 7 7  2 2 9 9] ...
      [9 9 9 9  9 9 9 9  9 9 9 9  9 9 9 9] ...
      [0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]];
  
p12 = [[12 12 12 12  12 12 12 12  12 12 12 12  12 12 11 11] ...
       [11 11 11 11  11 11 7 7  7 7 7 7  14 14 9 9] ...
      [9 9 9 9  9 9 9 9  9 9 9 9  9 9 9 9] ...
      [0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]];
  
p13 = [[12 12 12 12  12 12 12 12  12 12 12 12  12 12 11 11] ...
       [11 11 11 11  11 11 7 7  7 7 7 7  2 2 9 9] ...
      [9 9 9 9  9 9 9 9  9 9 7 7  9 9 11 11] ...
      [11 11 12 12  12 12 11 11  11 11 7 7  2 2 4 4]];
  
p14 = [[4 4 4 4  4 4 4 4  4 4 4 4  6 6 7 7] ...
       [7 7 7 7  7 7 2 2  2 2 7 7  14 14 9 9] ...
      [9 9 9 9  9 9 9 9  9 9 9 9  9 9 9 9] ...
      [0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0]];
  
% 
% p12 = [[3 3 3 -5 -5 -5 -2 -2 3 3 3 -5 -5 -5 -2 -2] ...
%       [2 2 2 -7 -7 -7 -2 -2 2 2 2 -7 -7 -7 -2 -2] ...
%       [0 0 0 -7 -7 -7 -2 -2 0 0 0 0 2 2 -2 -2] ...
%       [-5 -5 -2 -5 -5 -5 -2 -2 2 2 2 -5 -5 -5 -2 -2]];
pattern(1,:) =  [p11 p12 p13 p14];
pattern(2,:) =  [v1 v1 v2 v3];
pattern(3,:) =  [n1 n1 n2 n3];
seq.pattern = pattern;

porta.frequencyInput.set( 2e-3 );
porta.resonanceInput.set( 1.0 );
porta.bypass = true;

synth.vco1.detune = 0.2;
synth.vco1.voices = 4;
synth.vco1.stereospread = 0.4;
synth.vco1VolumeInput.set(1);

synth.vco2.detune = 0.4;
synth.vco2.voices = 4;
synth.vco2.stereospread = 1.0;
synth.vco2.tuning = 0;
synth.vco2VolumeInput.set(0.3);
synth.vco2.waveform = 'squarewave';

synth.noiseAmp.gainInput.set(0*0.3);
synth.noiseFilter.type = 'highpass';
synth.noiseFilter.frequencyInput.set(0.15);
synth.noiseGenerator.stereo = true;

% synth.cutoffInput.set( 1e-3 );
synth.cutoffInput.connect( filterModulation.output );
synth.resonanceInput.set( 0.35 );
synth.fenv.decayInput.set( 0.04 );
synth.fenv.sustainInput.set( 0.0005);
synth.fenv.attackInput.set( 0.001 );
synth.fenv.releaseInput.set( 0.15 );
synth.fenvAmount.gainInput.set( 0.15 );

synth.aenv.decayInput.set( 0.1 );
synth.aenv.releaseInput.set( 0.15 );
synth.aenv.attackInput.set( 1e-2 );
synth.aenv.sustainInput.set( 1 );

synth.penv.decayInput.set( 0.0015 );
synth.penv.releaseInput.set( 0.15 );
synth.penv.attackInput.set( 2e-3 );
synth.penv.sustainInput.set( 0 );
synth.penvAmount.gainInput.set( 100.0 );

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

sampleAndHold.decimationInput.set(2000/fs);
sampleAndHold.mix = 0.5;
sampleAndHold.bypass = true;

chorus.mix = 0.35;
chorus.frequency = 2;
chorus.bypass = true;
chorus.rightDelay = 0.03*fs;
chorus.leftDelay = 0.05*fs;

compressor.ratio = 0.3;
compressor.threshold = 0.5;
compressor.attack = 0.01;
compressor.release = 0.3;
compressor.bypass = false;

delayfx.wetmixInput.set( 1.0 );
delayfx.tap1Delay = noteLengthToSamples2(1/4, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.feedback = 0.5;
delayfx.bypass = false;

delayfx2.wetmixInput.set( 1.0 );
delayfx2.tap1Delay = noteLengthToSamples2(1/4, seq.bpm, fs);
delayfx2.tap2Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx2.feedback = 0.0;
delayfx2.bypass = true;

mixer.channels(1).sendLevelInput.set( 0.5 );
mixer.channels(1).levelInput.set( 1.0 );
mixer.channels(1).highShelfEq.bypass = false;
mixer.channels(1).highShelfEq.gainInput.set( 2.0 );
mixer.channels(1).highShelfEq.frequencyInput.set( 2*5000/fs );
mixer.channels(1).lowShelfEq.bypass = false;
mixer.channels(1).lowShelfEq.gainInput.set( 0.3 );
mixer.channels(1).lowShelfEq.frequencyInput.set( 2*400/fs );
mixer.channels(1).paramEq1.bypass = false;
mixer.channels(1).paramEq1.frequencyInput.set(2*1500/fs);
mixer.channels(1).paramEq1.gainInput.set( 0.5 );
mixer.channels(1).paramEq1.qInput.set( 0.1 );
mixer.channels(1).paramEq2.bypass = false;
mixer.channels(1).paramEq2.frequencyInput.set(2*300/fs);
mixer.channels(1).paramEq2.gainInput.set( 2 );
mixer.channels(1).paramEq2.qInput.set( 0.4 );

mixer2.channels(1).sendLevelInput.set( 0.005 );
mixer2.channels(1).highShelfEq.bypass = true;
mixer2.channels(1).highShelfEq.gainInput.set( 2.0 );
mixer2.channels(1).highShelfEq.frequencyInput.set( 2*5000/fs );

delayCompressor.useSidechainInput = true;
delayCompressor.ratio = 0.01;
delayCompressor.threshold = 0.2;
delayCompressor.attack = 0.001;
delayCompressor.release = 0.3;

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