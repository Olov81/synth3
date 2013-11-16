clear classes;
clc;
close all;

fs = 44100;
T = 3;
t = (0:T*fs-1)/fs;
N = length(t);

seq = MatrixSequencer('Sequencer', fs);
seq.bpm = 100;

synth = MonoSynth('Synth', fs);

synth.gateInput.connect( seq.gateOutput );
synth.cvInput.connect( seq.cvOutput );

synth.fenv.decayInput.set( 0.01 );
synth.fenv.sustainInput.set( 0 );
synth.fenvAmount.gainInput.set( 0.2 );

synth.update(N);

% plot( synth.output.read(N) );

sound( 0.2*synth.output.read(N), fs );