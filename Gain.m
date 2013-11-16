classdef Gain < Module
   
    properties
        
        gainInput
        input
        output
        
    end
    
    methods
        
        function this = Gain(name, initialGain)
           
            this = this@Module(name);
            
            g = 1;
            if( nargin > 1 )
                g = initialGain;
            end;
            
            this.gainInput = this.createInputPort( g );    
            this.input = this.createInputPort();
            this.output = this.createOutputPort();
            
        end
        
        function doUpdate(this, N)
           
            g = this.gainInput.read(N);
            x = this.input.read(N);
            
            this.output.write( g.*x );
            
        end
    end    
end
    