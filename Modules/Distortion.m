classdef Distortion < AudioEffect
   
    properties
       
        mix,
        drive
        
    end
    
    methods
        
        function this = Distortion(name)
           
            this = this@AudioEffect(name);
            
            this.mix = 1.0;
            this.drive = 2.0;
        end
        
        function updateFx(this, N)
           
            x = this.input.read(N);
            wet = atan(this.drive*x);
            y = this.mix*wet + (1-this.mix)*x;
            this.output.write( y );
            
        end
    end    
end