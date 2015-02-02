classdef AudioEffect < Module
   
    properties
        bypass
    end
    
    properties (SetAccess = private)
    
        input
        output

    end
    
    methods (Abstract)
        
        updateFx(this, N)
        
    end
    
    methods
       
        function this = AudioEffect(name)
        
            this = this@Module(name);
            
            this.input = this.createInputPort();
            this.output = this.createOutputPort();
            this.bypass = false;
            
        end
        
        function doUpdate(this, N)
           
            if( this.bypass )
                x = this.input.read(N);
                this.output.write(x);
            else
                updateFx(this, N);
            end
            
        end
        
        
    end
end