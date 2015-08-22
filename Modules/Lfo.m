classdef Lfo < Module
   
    properties(SetAccess = private)
        
        frequencyInput
        amplitudeInput
        gateInput
        
        output
    end
    
    properties(Access = private)
    
        fs
        
    end
    
    properties
    
        offset
        type
        syncDelay
        
    end
    
    methods
       
        function this = Lfo(name, fs)
           
            this = this@Module(name);
            this.fs = fs;
            this.offset = 0;
            this.type = 'free';
            this.syncDelay = 0;
            
            this.frequencyInput = this.createInputPort( 1.0 );
            this.amplitudeInput = this.createInputPort( 1.0 );
            this.gateInput = this.createInputPort();
            
            this.output = this.createOutputPort();
            
        end
        
        function doUpdate(this, N)
        
            fvec = this.frequencyInput.read(N);
            gate = this.gateInput.read(N);
            amplitude = this.amplitudeInput.read(N);
            
            t = 0;
            Ts = 1/this.fs;
            y = zeros(N, 1);
            oldGate = 0;
            gateThreshold = 1e-5;
            f = 0;
            
            for n = 1:N
              
                if( (gate(n) - oldGate) > gateThreshold )
                    t = 0;
                    f = 0;
                end;
                
                f = f + fvec(n);
                
                if( t > this.syncDelay )
                    y(n) = amplitude(n)*sin(2*pi*f*Ts) + this.offset;
                else
                    y(n) = 0;
                end;
                
                t = t + Ts;
                oldGate = gate(n);
                
            end;
            
            this.output.write( y );
            
        end
        
    end
end