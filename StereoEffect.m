classdef StereoEffect
   
    properties
        
        monoeffect
        
    end
    
    methods
       
        function this = StereoEffect(monoeffect)
            
            this.monoeffect = monoeffect;
            
        end;
        
        function y = update(this, x)
            
            monoeffect = this.monoeffect;
            
            dim = size(x);
            
            y = zeros(size(x));
            
            for( n = 1:dim(2) )
                
                y(:,n) = monoeffect.update(x(:,n));
                
            end;
        end;
    end
end