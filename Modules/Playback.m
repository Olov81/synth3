classdef Playback < Module
   
    properties(SetAccess = private)
   
        leftInput
        rightInput

    end
   
    properties
    
        volume
        fs
        
    end
    
    methods
       
        function this = Playback(name, fs)
           
            this = this@Module(name);
            
            this.leftInput = this.createInputPort();
            this.rightInput = this.createInputPort();
            this.volume = 0.5;
            this.fs = fs;
            
        end
        
        function doUpdate(this, N)
            
            y = [this.leftInput.read(N) this.rightInput.read(N)];
            
            sound(this.volume*y, this.fs);
            
        end;
    end
end