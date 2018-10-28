clear classes;
clc;
close all;

fs = 44100;
T = 15;
t = (0:T*fs-1)/fs;
N = length(t);


% Create modules
seq = MatrixSequencer('Sequencer', fs);
mixer = Mixer('Main mixer', 1);
mixer2 = Mixer('Mixer 2', 1);
vibrato = Lfo('Vibrato', fs);
synth = MonoSynth('Synth', fs);
synthHpf = TwoPoleFilter('Synth hpf');
distortion = Distortion('Distortion');
sampleAndHold = SampleAndHold('SampleAndHold');
filterModulation = CustomEnvelope('FilterModulation', fs);
chorus = Chorus('Chorus', fs);
compressor = Compressor('Compressor', fs);
delayfx = MultiTapDelay('Delay', fs);
delayfx2 = MultiTapDelay('Delay', fs);
delayCompressor = Compressor('Delay compressor', fs);
reverb = Reverb('Reverb', fs);
reverbHpf = TwoPoleFilter('Reverb hpf');
reverbCompressor = Compressor('Reverb compressor', fs);
writer = WaveWriter('Writer');
envelopeFollower = TwoPoleFilter('Envelope follower');
rectifier = Rectifier('Delay filter input rectifier');

% Connect everything up
synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( seq.cvOutput );
synthHpf.input.connect( synth.output );
distortion.input.connect( synthHpf.output );
sampleAndHold.input.connect( distortion.output );
chorus.input.connect( sampleAndHold.output );
mixer.channels(1).input.connect(chorus.output);
delayCompressor.sidechainInput.connect( mixer.sendOutput );
envelopeFollower.input.connect( mixer.sendOutput );
rectifier.input.connect( mixer.sendOutput );
envelopeFollower.frequencyInput.connect( rectifier.output );
delayfx.input.connect( envelopeFollower.output );
delayfx2.input.connect( delayfx.output );
delayCompressor.input.connect( delayfx2.output );
mixer.returnInput.connect(delayCompressor.output);
mixer2.channels(1).input.connect( mixer.mainOutput );
reverb.input.connect( mixer2.sendOutput );
reverbHpf.input.connect( reverb.output );
reverbCompressor.input.connect( reverbHpf.output );
reverbCompressor.sidechainInput.connect( synth.output );
mixer2.returnInput.connect( reverbCompressor.output );
compressor.input.connect( mixer2.mainOutput );
writer.input.connect( compressor.output );

% Set parameters
seq.bpm = 138;
seq.transpose = -12;

v1 = [1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0 ... 
      1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0 ... 
      1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0 ...  
      1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0]*1;
  
% n1 = [1 1 3 0  1 1 3 0  1 1 3 0  1 1 3 0 ... 
%       1 1 3 0  1 1 3 0  1 1 3 0  1 1 3 0 ...
%       1 1 3 0  1 1 3 0  1 1 3 0  1 1 3 0 ... 
%       1 1 3 0  1 1 3 0  1 1 3 0  1 1 3 0]*0.4;

  n1 = [1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0 ... 
        1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0 ... 
        1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0 ...  
        1 0 0 1  0 0 1 0  0 1 0 0  1 0 1 0]*0.85;
  
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
% p1 = [-2 -2 0 0     3 3 5 5     0 0 0 -12   	-12 -12 -12 0 ...
%        -2 -2 0 0     3 3 5 5     0 0 0 -12   	-12 -12 -12 0 ...
%        -2 -2 0 0     3 3 5 5     0 0 0 -12   	-12 -12 -12 0 ...
%        -2 -2 0 0     3 3 5 5     0 0 0 -12   	-12 -12 -12 0];
p1 = [12 12 12 7   7 7 12 12   12 7 7 7   	12 12 14 14 ...
      12 12 12 7   7 7 12 12   12 7 7 7   	12 12 7 7 ...
      17 17 17 12   12 12 17 17   17 12 12 12   	17 17 12 12 ...
      19 19 19 12   12 12 19 19   19 12 12 12   	19 19 12 12];
  
% 
% p1 = [[3 3 3 -5 -5 -5 -2 -2 3 3 3 -5 -5 -5 -2 -2] ...
%       [2 2 2 -7 -7 -7 -2 -2 2 2 2 -7 -7 -7 -2 -2] ...
%       [0 0 0 -7 -7 -7 -2 -2 0 0 0 0 2 2 -2 -2] ...
%       [-5 -5 -2 -5 -5 -5 -2 -2 2 2 2 -5 -5 -5 -2 -2]];
pattern(1,:) =  [p1 p1 p1 p1];
pattern(2,:) =  [v1 v1 v1 v1];
pattern(3,:) =  [n1 n1 n1 n1];
seq.pattern = pattern;

synth.vco1.detune = 0.4;
synth.vco1.voices = 8;
synth.vco1.stereospread = 0.5;
synth.vco1.tuning = 0;
synth.vco1VolumeInput.set(0.1);

synth.vco2.detune = 0.04;
synth.vco2.voices = 0;
synth.vco2.stereospread = 0.0;
synth.vco2.tuning = -12;
synth.vco2VolumeInput.set(0.1);

synth.noiseAmp.gainInput.set(0.05);
synth.noiseFilter.type = 'bandpass';
synth.noiseFilter.frequencyInput.set(0.15);
synth.noiseGenerator.stereo = true;

synth.cutoffInput.set( 0.1 );
synth.cutoffInput.connect( filterModulation.output );
synth.resonanceInput.set( 0.7 );
synth.fenv.decayInput.set( 0.5 );
synth.fenv.sustainInput.set( 0.00);
synth.fenv.attackInput.set( 1e-3 );
synth.fenv.releaseInput.set( 0.02 );
synth.fenvAmount.gainInput.set( 0.1 );
% synth.fenvAmount.gainInput.connect(filterModulation.output);

synth.aenv.decayInput.set( 0.03 );
synth.aenv.releaseInput.set( 0.1 );
synth.aenv.attackInput.set( 2e-2 );
synth.aenv.sustainInput.set( 0.3 );

synth.penv.decayInput.set( 0.0015 );
synth.penv.releaseInput.set( 0.05 );
synth.penv.attackInput.set( 2e-4 );
synth.penv.sustainInput.set( 1 );
synth.penvAmount.gainInput.set( 000.0 );

synth.flfo.amplitudeInput.set( 1 );
synth.flfo.frequencyInput.set( 6 );
synth.flfo.syncDelay = 0.0;

synth.portaRateInput.set( 0.002 );

synthHpf.type = 'highpass';
synthHpf.resonanceInput.set( 0.5 );
% synthHpf.frequencyInput.set( 450*2/fs );
synthHpf.frequencyInput.connect(filterModulation.output);
synthHpf.bypass = true;

p1.time = 0;
p1.value = 2*10/fs;
p2.time = 20;
p2.value = 2*15000/fs;
p3.time = 27;
p3.value = 2*20/fs;
filterModulation.points = [p1 p2 p3];

distortion.drive = 10;
distortion.bypass = true;

sampleAndHold.decimationInput.set(2000/fs);
sampleAndHold.mix = 1.0;
sampleAndHold.bypass = true;

chorus.mix = 0.35;
chorus.frequency = 2;
chorus.bypass = true;
chorus.rightDelay = 0.03*fs;
chorus.leftDelay = 0.05*fs;

compressor.ratio = 0.8;
compressor.threshold = 0.1;
compressor.attack = 0.05;
compressor.release = 0.3;
compressor.bypass = true;

delayfx.wetmixInput.set( 1.0 );
delayfx.tap1Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/16, seq.bpm, fs);
delayfx.feedback = 0.5;
delayfx.bypass = false;
envelopeFollower.resonanceInput.set( 0.5 );

delayfx2.wetmixInput.set( 1.0 );
delayfx2.tap1Delay = noteLengthToSamples2(1/128, seq.bpm, fs);
delayfx2.tap2Delay = noteLengthToSamples2(1/128, seq.bpm, fs);
delayfx2.feedback = 0.0;
delayfx2.bypass = true;

mixer.channels(1).sendLevelInput.set( 0.5 );
mixer.channels(1).levelInput.set( 1.5 );

mixer.channels(1).highShelfEq.bypass = true;
mixer.channels(1).highShelfEq.gainInput.set( 2.0 );
mixer.channels(1).highShelfEq.frequencyInput.set( 2*5000/fs );

mixer.channels(1).lowShelfEq.bypass = false;
mixer.channels(1).lowShelfEq.gainInput.set( 2 );
mixer.channels(1).lowShelfEq.frequencyInput.set( 2*110/fs );

mixer.channels(1).paramEq1.bypass = true;
mixer.channels(1).paramEq1.frequencyInput.set(2*1500/fs);
mixer.channels(1).paramEq1.gainInput.set( 0.5 );
mixer.channels(1).paramEq1.qInput.set( 0.1 );

mixer.channels(1).paramEq2.bypass = true;
mixer.channels(1).paramEq2.frequencyInput.set(2*300/fs);
mixer.channels(1).paramEq2.gainInput.set( 2 );
mixer.channels(1).paramEq2.qInput.set( 0.4 );

mixer2.channels(1).sendLevelInput.set( 0.005 );
mixer2.channels(1).highShelfEq.bypass = true;
mixer2.channels(1).highShelfEq.gainInput.set( 2.0 );
mixer2.channels(1).highShelfEq.frequencyInput.set( 2*5000/fs );

delayCompressor.useSidechainInput = true;
delayCompressor.ratio = 0.1;
delayCompressor.threshold = 0.7;
delayCompressor.attack = 0.001;
delayCompressor.release = 0.3;

reverb.time = 3.0;
reverb.mix = 1.0;
reverb.initialDelay = 0.2;
reverb.bypass = false;
reverb.hfFallOffRate = 0.9;
reverb.width = 1;

reverbHpf.type = 'highpass';
reverbHpf.resonanceInput.set( 0.9 );
reverbHpf.frequencyInput.set( 0.005 );

reverbCompressor.useSidechainInput = true;
reverbCompressor.ratio = 0.999;
reverbCompressor.threshold = 0.999;
reverbCompressor.attack = 0.01;
reverbCompressor.release = 0.15;
reverbCompressor.bypass = true;


tic
writer.update(N);
toc

% player.update(N);