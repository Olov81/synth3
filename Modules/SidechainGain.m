classdef SidechainGain < Module
    
    properties(SetAccess=private)
        attackInput
        releaseInput
%         floorInput
        output
        
        bpm
        hold        
        
        pulseGenerator
        envelope
        sum
        gain
    end
    
    properties(Access=private)
        fs
    end
    
    methods
       
        function this = SidechainGain(name, fs, bpm, hold)
            
            this = this@Module(name);
            
            this.pulseGenerator = this.addSubModule( PulseGenerator('SCG Pulse generator', fs, bpm, hold) );
            this.envelope = this.addSubModule( EnvelopeGenerator('SCG Envelope', fs) );
            this.sum = this.addSubModule( Sum('SCG Sum', 2) );
            this.gain = this.addSubModule( Gain('SCG Gain',1) );
            
            this.attackInput = this.envelope.attackInput;
            this.releaseInput = this.envelope.releaseInput;
            this.output = this.sum.output;
            
            this.envelope.gateInput.connect(this.pulseGenerator.output);
            this.gain.input.connect(this.envelope.output);
            this.gain.gainInput.set(1);
            this.sum.inputPorts(1).connect(this.gain.output);
            this.sum.inputPorts(2).set(1);
            
            this.attackInput.set(1e-2);
            this.releaseInput.set(0.2);
            this.envelope.sustainInput.set(1.0);
            
%             this.floorInput.set(0.1);
            
        end
        
        function doUpdate(this, N)
        
            
            
        end     
    end
end