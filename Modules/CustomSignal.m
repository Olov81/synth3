classdef CustomSignal < Module
    
    properties (SetAccess = private)
        output
    end
    
    properties
        signal
    end
    
    methods
        
        function this = CustomSignal(name)
            
            this = this@Module(name);
           
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this, N)
            
            signalLength = length(this.signal);
            y = this.signal(end)*ones(N,1);
            endIndex = min(signalLength, N);
            y(1:endIndex) = this.signal(1:endIndex);
          
            this.output.write(y);
        end;
            
	end 
end