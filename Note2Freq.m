classdef Note2Freq < AudioEffect
   
    properties (Access=private)
        
        f0
        
    end
    
    methods
        
        function this = Note2Freq(name, f0)
    
            this = this@AudioEffect(name);
            this.f0 = f0;
            
        end;
        
        function updateFx(this, N)
            
            x = this.input.read(N);
            
            y = this.f0*2.^(x*log2(1/this.f0));
            
            this.output.write( y );
            
        end;
        
    end
end