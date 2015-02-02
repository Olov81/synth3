classdef StereoEffect < EmptyModule
   
    properties
   
        
        monoeffect
        
    end
    
    methods
       
        function this = StereoEffect(monoeffect)
            
            this = this@EmptyModule(name);
            
            this.monoeffect = monoeffect;
            
        end;
        
        function y = doUpdate(this, x)
            
            dim = size(x);
            
            y = zeros(size(x));
            
            for( n = 1:dim(2) )
                
                y(:,n) = this.monoeffect.update(x(:,n));
                
            end;
        end;
    end
end