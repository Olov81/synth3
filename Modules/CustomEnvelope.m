classdef CustomEnvelope < Module
   
	properties(SetAccess = private)
        output
    end
    
    properties(Access = private)
        fs
    end
    
    properties
        points        
    end
    
    methods
        
        function this = CustomEnvelope(name, fs)
            
            this = this@Module(name);
           
            this.fs = fs;
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this, N)
            
            nextPointIndex = 1;
            numberOfPoints = length(this.points);
            t = 0;            
            if( this.points(nextPointIndex).time > 0 )
                v = 0;
            else
                v = this.points(nextPointIndex).value;
                nextPointIndex = nextPointIndex + 1;
            end;
            
            k = (this.points(nextPointIndex).value-v)/(this.points(nextPointIndex).time-t);
            Ts = 1/this.fs;
            y = zeros(N,1);
            for n = 1:N
                
                if( t > this.points(numberOfPoints).time )
                    k = 0;
                elseif( t > this.points(nextPointIndex).time )
                    nextPointIndex = nextPointIndex + 1;
                    v1 = this.points(nextPointIndex).value;
                    t1 = this.points(nextPointIndex).time;
                    k = (v1-v)/(t1-t);
                end;
                
                y(n) = v + k*Ts;
                v = y(n);
                t = t + Ts;
            end
            
            this.output.write( y );
        end
        
    end
end