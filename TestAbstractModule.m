
clear classes;
clc;
close all;
fs = 44100;
T = 3;
t = (0:T*fs-1)/fs;

% Audio signal chain
mainModule = EmptyModule('MainModule');
seq = MatrixSequencer('Sequencer',fs);
osc = SawtoothOscillator('Oscillator',fs);
vcf = MoogFilter('Filter',4);
amp = Gain('Amplifier');

pattern = seq.pattern;
pattern(1,:) = pattern(1,:) - 36;
seq.pattern = pattern;

% Modulation chain
ampLfo = SineWaveOscillator('Amp LFO', fs);
ampLfoFreq = Constant( 'Amp LFO freq', 2 );
cutoff = Constant( 'Filter cutoff', 0.3 );
resonance = Constant( 'Filter resonance', 0.5 );

mainModule.addSubModule( seq );
mainModule.addSubModule( osc );
mainModule.addSubModule( vcf );
mainModule.addSubModule( amp );

mainModule.addSubModule( cutoff );
mainModule.addSubModule( resonance );
mainModule.addSubModule( ampLfo );
mainModule.addSubModule( ampLfoFreq );

osc.frequencyInput.connect( seq.cvOutput );
vcf.input.connect( osc.waveformOutput );
vcf.cutoffFrequencyInput.connect( cutoff.output );
vcf.resonanceInput.connect( resonance.output );
amp.input.connect( vcf.output );
amp.gainInput.connect( ampLfo.output );
ampLfo.frequencyInput.connect( ampLfoFreq.output );

mainModule.update( length(t) );

plot( t, amp.output.read( length(t) ) );
