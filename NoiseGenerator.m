classdef NoiseGenerator < EmptyModule
   
    properties
        stereo
    end
    
    properties(SetAccess=private)
        output
    end
    
    methods
        
        function this = NoiseGenerator(name)

            this = this@EmptyModule(name);
            this.output = this.createOutputPort();
            this.stereo = false;
        end
        
        function doUpdate(this, N)
           
            if( this.stereo )
                numberOfChannels = 2;
            else
                numberOfChannels = 1;
            end;
            
            this.output.write( 2*rand(N, numberOfChannels)-1 );
            
        end
    end
end