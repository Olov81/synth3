classdef WaveWriter < Module
   
    properties(SetAccess = private)
   
        input
        y
        
    end
   
    methods
       
        function this = WaveWriter(name)
           
            this = this@Module(name);
            
            this.input = this.createInputPort();
            
        end
        
        function doUpdate(this, N)
            
            this.y = this.input.read(N);
            
        end;
    end
end