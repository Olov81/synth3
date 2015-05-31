
clear all;

fs = 44100;
T = 4;
N = T*fs;

sequencer = MatrixSequencer('Sequencer', fs);
player = SamplePlayer('Player', fs);
writer = WaveWriter('Writer');

player.gateInput.connect(sequencer.gateOutput);
writer.input.connect(player.output);

v = [1 2 3 4  4 0 0 4  0 0 4 0  4 1 2 3]/4;
v1 = [1 0 0 0  1 0 0 0  1 0 0 0  1 0 0 0];
n = [1 1 1 1  1 0 0 1  0 0 1 0  1 1 1 1]*0.9;
n1 = [1 0 0 0  1 0 0 0  1 0 0 0  1 0 0 0]*0.9;
p = [0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0];

pattern(1,:) =  [p p];
pattern(2,:) =  [v v1];
pattern(3,:) =  [n n1];

sequencer.bpm = 125;
sequencer.pattern = pattern;

player.sample = audioread('..\synth2\DrumSamples\MyTranceKicks\MyTranceKick51.wav');
player.ampEnvelope.decayInput.set( 0.1 );
player.ampEnvelope.sustainInput.set( 0.0 );
player.ampEnvelope.attackInput.set( 1e-4 );
player.ampEnvelope.releaseInput.set( 0.01 );

writer.update(N);

