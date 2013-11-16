classdef Constant < Module

    properties (Access = private)
        value
    end
  
    properties
        
        output
    end
    
    methods
        
        function this = Constant(name, value)
            
            this = this@Module(name);
            
            this.value = value;
            this.output = this.createOutputPort();
            
        end;
        
        function doUpdate(this, N)
        
            this.output.write( this.value*ones(N,1) );
            
        end;
        
    end
end