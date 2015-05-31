classdef LinearFilter < AudioEffect
   
	properties(Access = private)
        inputState
        outputState
        index
    end
    
    methods(Abstract)
    
        [B,A] = computeCoefficients(this, N)
        
    end
    
    methods
        
        function this = LinearFilter(name, order)
            
            this = this@AudioEffect(name);
           
            this.inputState = zeros(1,order+1);
            this.outputState = zeros(1,order+1);
            this.index = 0;
            
        end
        
        function updateFx(this, N)
            
            [x, numberOfChannels] = this.input.read(N);
            [B,A] = computeCoefficients(this, N);
            
            y = zeros(size(x));
            
            for channel = 1:numberOfChannels
                y(:,channel) = MexFastFilter(B', A', x(:,channel), this.inputState, this.outputState, this.index);
            end;
            
            this.output.write(y);
        end
        
    end
end