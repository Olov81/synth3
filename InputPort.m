classdef InputPort < handle
   
    properties (SetAccess = private)
    
        connection
        
    end
    
    methods
       
        function this = InputPort()
        
            this.connection = NoOutput;
            
        end;
        
        function connect(this, outputPort)
            
            this.connection = outputPort;
            
        end;
        
        function y = read(this, N)
            
            y = this.connection.read( N );
            
        end;
    end
end