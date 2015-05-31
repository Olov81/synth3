classdef ShelfEq < LinearFilter
   
    properties
        
        frequencyInput
        gainInput
        
    end
    
    properties(Access=private)
        invert
    end
    
    methods
        
        function this = ShelfEq(name, mode)
    
            this = this@LinearFilter(name, 2);
                        
            this.frequencyInput = this.createInputPort( 0.1 );
            this.gainInput = this.createInputPort( 1.2 );
            if(strcmp(mode,'high'))
                this.invert = -1;
            elseif(strcmp(mode,'low'))
                this.invert = 1;
            end;
        end;
        
        function [B,A] = computeCoefficients(this, N)
            
            frequency = this.frequencyInput.read(N);
            gain = this.gainInput.read(N);
            
            W0 = 2*atan( frequency );
            
            a = this.invert*(gain-1)./(gain+1);

            A = W0.*(1+a);
            B = W0.*(1-a);

            a0 = B + 1;
            a1 = B - 1;
            a2 = zeros(size(a0));

            b0 = A + 1;
            b1 = A - 1;
            b2 = zeros(size(b0));

            B = [b0 b1 b2];
            A = [a0 a1 a2];
                       
        end;
        
    end
end