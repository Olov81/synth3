classdef PulseGenerator < Module
    
    properties
        output 
    end
    
    properties(Access = private)
        fs
        pulsewidth
        frequency
    end
    
    methods
        
        function this = PulseGenerator(name, fs, bpm, pulsewidth)
            
            this = this@Module(name);
            
            this.frequency = bpm/60;
            this.pulsewidth = pulsewidth;
            this.fs = fs;
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this, N)
            
            t = (0:N-1)'/this.fs;
            
            y = (square(2*pi*this.frequency*t, this.pulsewidth)+1)/2;
            
            this.output.write( y );
        end;
    end
end