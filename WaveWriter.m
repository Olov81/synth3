classdef WaveWriter < Module
   
    properties(SetAccess = private)
   
        leftInput
        rightInput
        y
        
    end
   
    methods
       
        function this = WaveWriter(name)
           
            this = this@Module(name);
            
            this.leftInput = this.createInputPort();
            this.rightInput = this.createInputPort();
            
        end
        
        function doUpdate(this, N)
            
            this.y = [this.leftInput.read(N) this.rightInput.read(N)];
            
        end;
    end
end