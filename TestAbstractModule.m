
clear classes;
clc;
close all;
fs = 44100;
T = 0.1;
t = (0:T*fs-1)/fs;

mainModule = EmptyModule;
mainModule.name = 'MainModule';

osc = SawtoothOscillator(fs);
osc.name = 'Oscillator';

vcf = MoogFilter(4);
vcf.name = 'Filter';

freq = Constant( 100 );
freq.name = 'Frequency input';
cutoff = Constant( 0.1 );
cutoff.name = 'Cutoff input';
resonance = Constant( 0.5 );
resonance.name = 'Resonance input';

mainModule.addSubModule( vcf );
mainModule.addSubModule( freq );
mainModule.addSubModule( cutoff );
mainModule.addSubModule( resonance );
mainModule.addSubModule( osc );

osc.frequencyInput.connect( freq.output );
vcf.signalInput.connect( osc.waveformOutput );
vcf.cutoffFrequencyInput.connect( cutoff.output );
vcf.resonanceInput.connect( resonance.output );

mainModule.update( length(t) );

plot( t, vcf.signalOutput.read( length(t) ) );
