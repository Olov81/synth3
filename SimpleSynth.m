classdef SimpleSynth < Module

    properties
        
        soundOutput
        
    end
    
    methods
        
        function this = SimpleSynth(fs)
            
            osc = this.addSubModule( SawtoothOscillator(fs) );
            vcf = this.addSubModule( MoogFilter(4) );
            source = this.addSubModule( DummyModule );
            
            freq = source.createOutputPort;
            cutoff = source.createOutputPort;
            resonance = source.createOutputPort;
            
            osc.frequencyInput.connect( freq );
            vcf.cutoffFrequencyInput.connect( cutoff );
            vcf.resonanceInput.connect( resonance );
            
            freq.write( 100*ones(fs, 1) );
            cutoff.write( 0.1 );
            resonance.write( 0.5 );
            
            vcf.signalInput.connect( osc.waveformOutput );
            
            this.soundOutput = vcf.signalOutput;
            
        end;
        
        function doUpdate(this)
        end;
    end
end