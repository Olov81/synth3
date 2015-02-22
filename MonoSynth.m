classdef MonoSynth < EmptyModule
   
    properties(SetAccess=private)
        
        gateInput
        cvInput
        vco1VolumeInput
        vco2VolumeInput
        cutoffInput
        resonanceInput
        
        output
        
        flfo
        
        fenv
        fenvAmount
        
        penv
        penvAmount
        
        aenv
        
        vco1
        vco2
        noiseGenerator
        noiseAmp
        noiseFilter
    end
    
    properties(Access=private)
        
        vco1Gain
        vco2Gain

        vcf
        vca
        
        vcoSum
        cutoffSum
        
        pitchSum
        
        fenvMapper
        penvMapper
        
    end
    
    methods
        
        function this = MonoSynth(name,fs)
           
            this = this@EmptyModule(name);
            
            this.gateInput = this.createInputPort();
            this.cvInput = this.createInputPort();
            
            this.vco1VolumeInput = this.createInputPort();
            this.vco2VolumeInput = this.createInputPort();
            
            this.cutoffInput = this.createInputPort();
            this.resonanceInput = this.createInputPort();
            
            this.vco1 = this.addSubModule( MultiOscillator('VCO 1') );
            this.vco1Gain = this.addSubModule( Gain('VCO 1 Volume', 1 ) );
            this.vco2 = this.addSubModule( MultiOscillator('VCO 2') );
            this.vco2Gain = this.addSubModule( Gain('VCO 2 Volume', 1 ) );
            this.noiseGenerator = this.addSubModule( NoiseGenerator('Noise Generator') );
            this.noiseAmp = this.addSubModule( Gain('Noise Amp', 0) );
            this.noiseFilter = this.addSubModule(TwoPoleFilter('Noise filter'));
            
            this.vcf = this.addSubModule( MoogFilter('VCF', 4) );
            this.vca = this.addSubModule( Gain('VCA', 1) );
            this.fenv = this.addSubModule( EnvelopeGenerator('VCF Env', fs) );
            this.penv = this.addSubModule( EnvelopeGenerator('Pitch Env', fs) );
            this.aenv = this.addSubModule( EnvelopeGenerator('VCA Env', fs) );
            this.flfo = this.addSubModule( Lfo('Frequency LFO', fs) );
            this.fenvAmount = this.addSubModule( Gain('VCF Env Amount', 1) );
            this.penvAmount = this.addSubModule( Gain('Pich Env Amount', 0) );
            this.cutoffSum = this.addSubModule( Sum('Cutoff control',2) );
            this.vcoSum = this.addSubModule( Sum('VCO mix',3) );
            this.pitchSum = this.addSubModule( Sum('Pitch mix',3) );
            this.fenvMapper = this.addSubModule( Note2Freq('Filter env mapper', 2*20/fs) );
            this.penvMapper = this.addSubModule( Note2Freq('Pitch env mapper', 2*20/fs) );
            
            % Connect audio signal chain
            this.penv.gateInput.connect( this.gateInput );
            this.penvMapper.input.connect( this.penv.output );
            this.pitchSum.inputPorts(1).connect( this.cvInput );
            this.penvAmount.input.connect( this.penvMapper.output );
            this.pitchSum.inputPorts(2).connect( this.penvAmount.output );
            this.pitchSum.inputPorts(3).connect( this.flfo.output );
            this.vco1.frequencyInput.connect( this.pitchSum.output );
            this.vco2.frequencyInput.connect( this.pitchSum.output );
            this.noiseAmp.input.connect( this.noiseGenerator.output );
            this.noiseFilter.input.connect( this.noiseAmp.output );
            this.vco1Gain.input.connect( this.vco1.output );
            this.vco1Gain.gainInput.connect( this.vco1VolumeInput );
            this.vco2Gain.input.connect( this.vco2.output );
            this.vco2Gain.gainInput.connect( this.vco2VolumeInput );
            this.vcoSum.inputPorts(1).connect( this.vco1Gain.output );
            this.vcoSum.inputPorts(2).connect( this.vco2Gain.output );
            this.vcoSum.inputPorts(3).connect( this.noiseFilter.output );
            this.vcf.input.connect( this.vcoSum.output );
            this.vca.input.connect( this.vcf.output );
            
            % Filter modulation chain
            this.fenv.gateInput.connect( this.gateInput );
            this.fenvMapper.input.connect( this.fenv.output );
            this.fenvAmount.input.connect( this.fenvMapper.output );
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
            
            this.penv.attackInput.set( 1e-3 );
            this.penv.decayInput.set( 0.5 );
            this.penv.sustainInput.set( 0.0 );
            this.penv.releaseInput.set( 0.01 );
            this.penvMapper.bypass = true;
            
            this.aenv.attackInput.set( 1e-3 );
            this.aenv.decayInput.set( 0.5 );
            this.aenv.sustainInput.set( 0.0 );
            this.aenv.releaseInput.set( 0.2 );
            
            this.output = this.vca.output;
        end
    end
end