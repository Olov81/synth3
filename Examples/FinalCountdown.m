clear classes;
clc;
close all;

fs = 44100;
T = 8.5;
t = (0:T*fs-1)/fs;
N = length(t);

% Create modules
seq = MatrixSequencer('sequencer', fs);

pitchEnvelope = EnvelopeGenerator('pitch env', fs);
pitchEnvelope.gateInput.connect( seq.gateOutput );
pitchEnvelope.sustainInput.set(0);
pitchEnvelope.decayInput.set(0.005);
pitchEnvelope.attackInput.set(1e-4);
pitchEnvelope.releaseInput.set(1e-4);
pitchEnvelopeGain = Gain('pitch env gain', 1 );
pitchEnvelopeGain.input.connect(pitchEnvelope.output);
pitchEnvelopeGain.gainInput.set(90);

vcoPitchMix = Sum('vco pitch mix',2);
vcoPitchMix.inputPorts(1).connect(seq.cvOutput);
vcoPitchMix.inputPorts(2).connect(pitchEnvelopeGain.output);

vco = MultiOscillator('vco');
vco.voices = 2;
vco.stereospread = 0.0;
vco.detune = 0.08;
vco.frequencyInput.connect( vcoPitchMix.output );

vcfEnvelope = EnvelopeGenerator('vcf env', fs);
vcfEnvelope.gateInput.connect( seq.gateOutput );
vcfEnvelope.sustainInput.set(0.3);
vcfEnvelope.decayInput.set(0.03);
vcfEnvelope.attackInput.set(0.02);
vcfEnvelope.releaseInput.set(7e-3);
vcfEnvelopeGain = Gain('vcf env gain', 1 );
vcfEnvelopeGain.input.connect(vcfEnvelope.output);
vcfEnvelopeGain.gainInput.set(2);

vcf = MoogFilter('vcf', 4);
vcf.cutoffFrequencyInput.connect(vcfEnvelopeGain.output);
vcf.input.connect( vco.output );

vcaEnvelope = EnvelopeGenerator('vca env', fs);
vcaEnvelope.gateInput.connect( seq.gateOutput );
vcaEnvelope.sustainInput.set(1.0);
vcaEnvelope.attackInput.set(1e-2);
vcaEnvelope.releaseInput.set(0.05);

vca = Gain('vca', 1);
vca.input.connect( vcf.output );
vca.gainInput.connect( vcaEnvelope.output );

delayfx = MultiTapDelay('delay', fs);
delayfx.input.connect(vca.output);
delayfx.wetmixInput.set( 0.12 );
delayfx.feedback = 0.2;
delayfx.tap1Delay = noteLengthToSamples2(1/16, seq.bpm, fs);
delayfx.tap2Delay = noteLengthToSamples2(3/16, seq.bpm, fs);

chorus = Chorus('Chorus', fs);
chorus.input.connect(delayfx.output);
chorus.frequency = 2;
chorus.rightDelay = 0.002*fs;
chorus.leftDelay = 0.0*fs;

writer = WaveWriter('writer');
writer.input.connect( chorus.output );

% Set parameters
seq.bpm = 112;
seq.transpose = -3;
seq.loop = true;
v = [0 0 0 0  0 0 1 1  1 0 0 0  1 0 0 0 ...
     0 0 0 0  0 0 1 1  1 0 1 0  1 0 0 0 ...
     0 0 0 0  0 0 1 1  1 0 0 0  1 0 0 0 ...
     0 0 0 0  0 0 1 1  1 0 1 0  1 0 1 0];
n = [0 0 0 0  0 0 1 1  4 0 0 0  4.8 0 0 0 ...
     0 0 0 0  0 0 1 1  1 0 1 0  4.8 0 0 0 ...
     0 0 0 0  0 0 1 1  4 0 0 0  4.8 0 0 0 ...
     0 0 0 0  0 0 1 1  1 0 1 0  1 0 1 0].*0.8;
p = [0 0 0 0  0 0 7 5  7 7 7 7  0 0 0 0 ...
     0 0 0 0  0 0 8 7  8 8 7 7  5 5 5 5 ...
     5 5 5 5  5 5 8 7  8 8 8 8  0 0 0 0 ...
     0 0 0 0  0 0 5 3  5 5 3 3  2 2 5 5]; 
pattern(1,:) =  p;
pattern(2,:) =  v;
pattern(3,:) =  n;
seq.pattern = pattern;

writer.update(N);