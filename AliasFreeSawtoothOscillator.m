classdef AliasFreeSawtoothOscillator < Module
    
    properties (SetAccess = private)
        frequencyInput
        output
    end
    
    properties
        phaseshift
    end
    
    methods
        
        function this = AliasFreeSawtoothOscillator(name)
            
            this = this@Module(name);
            
            this.frequencyInput = this.createInputPort();
            this.output = this.createOutputPort();
            
            this.phaseshift = 0;
            
        end
        
        function doUpdate(this, N)
           
            freq = this.frequencyInput.read(N);           

            y = MexAliasFreeSaw(N, freq, this.phaseshift);
            
            this.output.write(y);
            
        end;
            
    end 
    
end