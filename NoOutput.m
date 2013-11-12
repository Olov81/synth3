classdef NoOutput
    
    properties
    
        owner
        
    end
    
    methods
       
        function this = NoOutput()
            
            this.owner = DummyModule;
            this.owner.name = 'Input termination';
            
        end;
        
        function y = read(this)
            
            y = 0;
            
        end;
        
    end

end