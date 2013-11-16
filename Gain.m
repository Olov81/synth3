classdef Gain < Module
   
    properties
        
        gainInput
        input
        output
        
    end
    
    methods
        
        function this = Gain(name)
           
            this = this@Module(name);
            
            this.gainInput = this.createInputPort();
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
    