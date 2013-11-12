classdef Constant < Module

    properties (Access = private)
        value
    end
  
    properties
        outputPort
    end
    
    methods
        
        function this = Constant(value)
            
            this.value = value;
            this.outputPort = createOutputPort();
            
        end;
        
        function doUpdate(this)
        
            this.outputPort.write( this.value );
            
        end;
end