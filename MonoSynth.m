classdef MonoSynth < EmptyModule
   
    properties(SetAccess=private)
        
        gateInput
        cvInput
        output
        
        cutoffInput
        resonanceInput
        
        fenv
        fenvAmount
        
        aenv
        
        vco1Tune
    end
    
    properties(Access=private)
        
        vco1
        vco2
        vcf
        vca
        
        vcoSum
        cutoffSum
    end
    
    methods
        
        function this = MonoSynth(name,fs)
           
            this = this@EmptyModule(name);
            
            this.gateInput = this.createInputPort();
            this.cvInput = this.createInputPort();
            
            this.cutoffInput = this.createInputPort();
            this.resonanceInput = this.createInputPort();
            
            this.vco1Tune = this.createInputPort();
            
            this.vco1 = this.addSubModule( AliasFreeSawtoothOscillator('VCO 1') );
            this.vco2 = this.addSubModule( AliasFreeSawtoothOscillator('VCO 2') );
            this.vcf = this.addSubModule( MoogFilter('VCF', 4) );
            this.vca = this.addSubModule( Gain('VCA', 1) );
            this.fenv = this.addSubModule( EnvelopeGenerator('VCF Env', fs) );
            this.aenv = this.addSubModule( EnvelopeGenerator('VCA Env', fs) );
            this.fenvAmount = this.addSubModule( Gain('VCF Env Amount', 1) );
            this.cutoffSum = this.addSubModule( Sum('Cutoff control',2) );
            this.vcoSum = this.addSubModule( Sum('VCO mix',2) );
            
            % Connect audio signal chain
            this.vco1.frequencyInput.connect( this.cvInput );
            this.vco1.fineTuneInput.connect( this.vco1Tune );
            this.vco2.frequencyInput.connect( this.cvInput );
            this.vco2.phaseshift = 0.2;
            this.vcoSum.inputPorts(1).connect( this.vco1.output );
            this.vcoSum.inputPorts(2).connect( this.vco2.output );
            
            this.vcf.input.connect( this.vcoSum.output );
            this.vca.input.connect( this.vcf.output );
            
            % Filter modulation chain
            this.fenv.gateInput.connect( this.gateInput );
            this.fenvAmount.input.connect( this.fenv.output );
            this.cutoffSum.inputPorts(1).connect( this.fenvAmount.output );
            this.cutoffSum.inputPorts(2).connect( this.cutoffInput );
            
            this.vcf.cutoffFrequencyInput.connect( this.cutoffSum.output );
            this.vcf.resonanceInput.connect( this.resonanceInput );
            
            % Amplitude modulation chain
            this.vca.gainInput.connect( this.aenv.output );
            this.aenv.gateInput.connect( this.gateInput );
            
            % Default values
            this.fenv.attackInput.set( 1e-3 );
            this.fenv.decayInput.set( 0.5 );
            this.fenv.sustainInput.set( 0.1 );
            this.fenv.releaseInput.set( 0.2 );
            
            this.aenv.attackInput.set( 1e-3 );
            this.aenv.decayInput.set( 0.5 );
            this.aenv.sustainInput.set( 0.0 );
            this.aenv.releaseInput.set( 0.2 );
            
            this.output = this.vca.output;
        end
    end
end