
clear classes;
clc;
close all;
fs = 44100;
T = 5;
t = (0:T*fs-1)/fs;

mainModule = DummyModule;
mainModule.name = 'MainModule';

sourceModule = DummyModule;
sourceModule.name = 'SourceModule';

osc = SawtoothOscillator(fs);
osc.name = 'Oscillator';

vcf = MoogFilter(4);
vcf.name = 'Filter';

mainModule.addSubModule( osc );
mainModule.addSubModule( vcf );
mainModule.addSubModule( sourceModule );

freq = sourceModule.createOutputPort();
cutoff = sourceModule.createOutputPort();
resonance = sourceModule.createOutputPort();

osc.frequencyInput.connect( freq );
vcf.signalInput.connect( osc.waveformOutput );
vcf.cutoffFrequencyInput.connect( cutoff );
vcf.resonanceInput.connect( resonance );

freq.write( 100*(sin(2*pi*1*t)+1) + 1 );
cutoff.write( 0.1 );
resonance.write( 0.5 );

mainModule.update();

plot( t, vcf.signalOutput.read() );
