classdef MonoSynth < EmptyModule
   
    properties(SetAccess=private)
        
        gateInput
        cvInput
        output
        
        fenv
        fenvAmount
    end
    
    properties(Access=private)
        
        vco
        vcf
        vca
        
    end
    
    methods
        
        function this = MonoSynth(name,fs)
           
            this = this@EmptyModule(name);
            
            this.gateInput = this.createInputPort();
            this.cvInput = this.createInputPort();
           
            this.vco = this.addSubModule( SawtoothOscillator('VCO', fs) );
            this.vcf = this.addSubModule( MoogFilter('VCF', 4) );
            this.vca = this.addSubModule( Gain('VCA', 1) );
            this.fenv = this.addSubModule( EnvelopeGenerator('VCF Env', fs) );
            this.fenvAmount = this.addSubModule( Gain('VCF Env Amout', 1) );
            
            % Connect audio signal chain
            this.vco.frequencyInput.connect( this.cvInput );
            this.vcf.input.connect( this.vco.output );
            this.fenvAmount.input.connect(  this.fenv.output );
            this.vcf.cutoffFrequencyInput.connect( this.fenvAmount.output );
            this.vca.input.connect( this.vcf.output );
            
            % Connect modulation signals
            this.fenv.gateInput.connect( this.gateInput );
            this.fenv.attackInput.set( 1e-2 );
            this.fenv.decayInput.set( 0.5 );
            this.fenv.sustainInput.set( 0.1 );
            this.fenv.releaseInput.set( 0.2 );
            
            this.output = this.vca.output;
        end
    end
end