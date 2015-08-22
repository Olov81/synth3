classdef SineWaveOscillator < Module
    
    properties(SetAccess=private)
        frequencyInput
        gateInput
        output
    end
    
    properties
        phaseoffset
    end
    
    properties(Access=private)
        Ts
    end
    
    methods
       
        function this = SineWaveOscillator(name, fs)
            
            this = this@Module(name);
            
            this.Ts = 1/fs;
            this.frequencyInput = this.createInputPort();
            this.gateInput = this.createInputPort();
            this.output = this.createOutputPort();
            this.phaseoffset = 0;
            
        end
        
        function doUpdate(this, N)
        
            fvec = this.frequencyInput.read(N);
            gate = this.gateInput.read(N);
            oldgate = 0;
            threshold = 1e-3;
            y = zeros(size(fvec));
            f = 0;
            
            for n = 1:N
                
                if (gate(n) - oldgate) > threshold
                    f = 0;
                end
                
                f = f + fvec(n);
                y(n) = sin(2*pi*f*this.Ts + this.phaseoffset);
                oldgate = gate(n);
                
            end
            
            this.output.write( y );
        end     
    end
end