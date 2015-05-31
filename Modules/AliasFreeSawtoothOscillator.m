classdef AliasFreeSawtoothOscillator < Module
    
    properties (SetAccess = private)
        frequencyInput
        fineTuneInput
        output
    end
    
    properties
        phaseshift
        voices
        detune
    end
    
    methods
        
        function this = AliasFreeSawtoothOscillator(name)
            
            this = this@Module(name);
            
            this.frequencyInput = this.createInputPort();
            this.fineTuneInput = this.createInputPort();
            this.output = this.createOutputPort();
            
            this.phaseshift = 0;
            this.voices = 1;
            this.detune = 0;
        end
        
        function doUpdate(this, N)
           
            freq = this.frequencyInput.read(N);           
            fine = this.fineTuneInput.read(N);
           
            freq = freq.*(2.^(fine/12));
            
            disp('Generating cpp saw');
            tic
            y = MexAliasFreeSaw(N, freq, this.phaseshift);
            toc
            
            disp('Generating c saw');
            tic
            y = MexAliasFreeSawC(N, freq, this.phaseshift);
            toc
            
            this.output.write(y);
            
        end;
            
    end 
    
end