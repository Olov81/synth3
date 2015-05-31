classdef ParametricEq < LinearFilter
   
	properties
        frequencyInput
        gainInput
        qInput
        type
    end
    
    methods
        
        function this = ParametricEq(name)
            
            this = this@LinearFilter(name, 2);
           
            this.frequencyInput = this.createInputPort(0.1);
            this.gainInput = this.createInputPort(1.2);
            this.qInput = this.createInputPort(0.1);
            
        end
        
        function [B,A] = computeCoefficients(this, N)
        
            Omega = this.frequencyInput.read(N);
            Q = this.qInput.read(N);
            G = this.gainInput.read(N);
            
            W0 = 2*atan( Omega );

            ap = 1./G;
            az = ap.*G;

            A = az.*W0./Q;
            B = W0.^2;
            C = ap.*W0./Q;
            D = W0.^2;

            a0 = 1 + C + D;
            a1 = 2*D - 2;
            a2 = 1 - C + D;

            b0 = 1 + A + B; 
            b1 = 2*B - 2;
            b2 = 1 - A + B;

            A = [a0 a1 a2];
            B = [b0 b1 b2];
            
        end
    end
end
