clear classes;
clc;
close all;

fs = 44100;
T = 15;
t = (0:T*fs-1)/fs;
N = length(t);

seq = MatrixSequencer('Sequencer', fs);
seq.bpm = 138;
seq.transpose = 0;

v1 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ... 
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0]*1;
n1 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0]/1.01;
p1 = [2 2 0 0 3 3 3 0 0 0 3 3 3 10 3 3 ...
      8 8 7 7 3 3 3 0 0 0 3 3 3 0 7 7 ...
      5 5 2 2 5 5 5 2 2 2 5 5 5 7 5 5 ...
      15 15 14 14 5 5 5 2 2 2 5 5 5 5 10 10 ];
  
v2 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 1 1 1 0]*1;
n2 = [1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 0 1 1 0 ...
      1 0 1 0 1 0 0 1 0 0 1 0 1 1 1 0]/1.01;
p2 = [7 7 0 0 5 5 5 0 0 0 5 5 5 10 5 5 ...
      15 15 8 8 10 10 10 8 8 8 10 10 10 3 5 5 ...
      5 5 3 3 5 5 5 3 3 3 5 5 5 3 5 5 ...
      10 10 5 5 3 3 3 2 2 2 3 3 0 3 5 5 ];
  
pattern(1,:) = [p1 p2];
pattern(2,:) = [v1 v2];
pattern(3,:) = [n1 n2];

seq.pattern = pattern;

synth = MonoSynth('Synth', fs);
delayfx = MultiTapDelay('Delay', fs);
writer = WaveWriter('Writer');

synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( seq.cvOutput );
delayfx.input.connect( synth.output );
delayfx.wetmixInput.set( 0.3 );

synth.vco1Tune.set( 0.05 );
synth.fenv.decayInput.set( 0.03 );
synth.fenv.sustainInput.set( 0 );
synth.fenv.attackInput.set( 1e-4 );
synth.fenv.releaseInput.set( 0.03 );

synth.aenv.decayInput.set( 0.04 );
synth.aenv.releaseInput.set( 0.01 );

synth.fenvAmount.gainInput.set( 0.2 );
synth.resonanceInput.set( 0.1 );
synth.cutoffInput.set( 0.5 );

delayfx.tap1Delay = noteLengthToSamples2(1/8, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(1/8, seq.bpm, fs);

writer.leftInput.connect( delayfx.output1 );
writer.rightInput.connect( delayfx.output2 );

tic
writer.update(N);
toc

% player.update(N);