clear classes;
clc;
close all;

fs = 44100;
T = 8;
t = (0:T*fs-1)/fs;
N = length(t);

seq = MatrixSequencer('Sequencer', fs);
seq.bpm = 120;
seq.transpose = 5;

synth = MonoSynth('Synth', fs);

synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( seq.cvOutput );

synth.vco1Tune.set( 0.997 );
synth.fenv.decayInput.set( 0.03 );
synth.fenv.sustainInput.set( 0 );
synth.fenv.attackInput.set( 1e-5 );
synth.fenv.releaseInput.set( 0.05 );

synth.aenv.decayInput.set( 0.02 );
synth.aenv.releaseInput.set( 0.05 );

synth.fenvAmount.gainInput.set( 0.2 );
synth.resonanceInput.set( 0.2 );
synth.cutoffInput.set( 0.001 );

synth.update(N);

% plot( synth.output.read(N) );

sound( 0.5*synth.output.read(N), fs );