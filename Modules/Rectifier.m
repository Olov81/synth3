classdef Rectifier < AudioEffect
    
    properties(SetAccess=private)    
        
    end
        
    methods
       
        function this = Rectifier(name)
           
            this = this@AudioEffect(name);
        end
        
        function updateFx(this,N)
            
            x = this.input.read(N);
            
            x = 0.15*(x(:,1) + 0.1);
            
            this.output.write(abs(x));
            
        end
    end
end