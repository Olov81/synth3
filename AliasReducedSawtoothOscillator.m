classdef AliasReducedSawtoothOscillator < Module
    
    properties (SetAccess = private)
        frequencyInput
%         phaseshiftInput
        output
    end
    
    properties (Access = private)
    
        ts
        order
        
        scale        
        c1
        c2
        lambda
        C_

    end
    
    methods
        
        function this = AliasReducedSawtoothOscillator(name, fs, order)
            
            this = this@Module(name);
            
            this.scale = 1000;
            
            this.ts = 1/(fs/this.scale);
            this.order = order;
            
            this.frequencyInput = this.createInputPort();
%             this.phaseshiftInput = this.createInputPort();
            this.output = this.createOutputPort();
            
            this.computeFilter();
            
        end
        
        function doUpdate(this, N)
           
            freq = this.frequencyInput.read(N)/this.scale;
%             phaseshift = this.phaseshiftInput.read(N);
            
            y = zeros(N,1);
            I = zeros(this.order,1);
            w = zeros(this.order,1);
            
            t = 0;
            
            for( n = 1:length(y) )
    
                T = 1/freq(n);

                t0 = t;
                t = t + this.ts;

                k = freq(n);

                if( t > T )

                    for( m = 1:this.order )

                        I(m) = (this.lambda(m)*t0 + 1)*exp(this.lambda(m)*(t-t0)) + (1 - exp(this.lambda(m)*(t-T)))*this.lambda(m)*T - this.lambda(m)*t - 1;

                        w(m) = this.c1(m)*w(m) + k*this.c2(m)*I(m);

                        y(n) = y(n) + real(this.C_(m)*w(m));

                    end;

                    t = t - T;

                else

                    for( m = 1:this.order )

                        I(m) = (this.lambda(m)*t0 + 1)*this.c1(m) - this.lambda(m)*t - 1;

                        w(m) = this.c1(m)*w(m) + k*this.c2(m)*I(m);

                        y(n) = y(n) + real(this.C_(m)*w(m));

                    end;

                end;

            end;

            this.output.write(2*y-1);

        end;
            
    end 
    
    methods (Access = private)
    
        function computeFilter(this)
            
            [A,B,C,D] = ellip(this.order, 1, 60, pi/this.ts, 'low', 's');

            [P, LAMBDA] = eig(A);

            this.C_ = C*P;
            B_ = P\B;
            this.lambda = diag(LAMBDA);

            this.c1 = exp(this.lambda*this.ts);
            this.c2 = B_./(this.lambda.^2);

        end;
    end;
    
end