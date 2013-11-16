classdef SineWaveOscillator < Module
    
    properties(SetAccess=private)
        frequencyInput
        output
    end
    
    properties(Access=private)
        fs
    end
    
    methods
       
        function this = SineWaveOscillator(name, fs)
            
            this = this@Module(name);
            
            this.fs = fs;
            this.frequencyInput = this.createInputPort();
            this.output = this.createOutputPort();
            
        end
        
        function doUpdate(this, N)
        
            t = (0:N-1)'/this.fs;
            f = this.frequencyInput.read(N);
            
            this.output.write( sin(2*pi*f.*t) );
            
        end     
    end
end