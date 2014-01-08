classdef AliasFreeSawtoothOscillator < Module
    
    properties (SetAccess = private)
        frequencyInput
        fineTuneInput
        output
    end
    
    properties
        phaseshift
    end
    
    methods
        
        function this = AliasFreeSawtoothOscillator(name)
            
            this = this@Module(name);
            
            this.frequencyInput = this.createInputPort();
            this.fineTuneInput = this.createInputPort();
            this.output = this.createOutputPort();
            
            this.phaseshift = 0;
            
        end
        
        function doUpdate(this, N)
           
            freq = this.frequencyInput.read(N);           
            fine = this.fineTuneInput.read(N);
            
            freq = freq.*(2.^(fine/12));
            
            y = MexAliasFreeSaw(N, freq, this.phaseshift);
            
            this.output.write(y);
            
        end;
            
    end 
    
end