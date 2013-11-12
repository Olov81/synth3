classdef OutputPort < handle

    properties (SetAccess = private)
    
        data
        owner
    end
    
    methods
        
        function this = OutputPort(owner)
            
            this.data = 0;
            this.owner = owner;
        end;
        
        function write(this, data)
            
            this.data = data;
            
        end;
        
        function y = read(this, N)
            
            y = this.data;
            
        end;
    end
end