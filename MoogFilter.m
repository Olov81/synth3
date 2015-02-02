classdef MoogFilter < AudioEffect
   
    properties
        
        numberOfStages
        temperatureConstant
        
        cutoffFrequencyInput
        resonanceInput
        
    end
    
    methods
        
        function this = MoogFilter(name, numberOfStages)
    
            this = this@AudioEffect(name);
            this.numberOfStages = numberOfStages;
            this.temperatureConstant = 1;
                        
            this.cutoffFrequencyInput = this.createInputPort( 0.5 );
            this.resonanceInput = this.createInputPort( 0.1 );
            
        end;
        
        function updateFx(this, N)
            
            [x, numberOfChannels] = this.input.read(N);
            
            FcN = this.cutoffFrequencyInput.read(N);
            r = this.resonanceInput.read(N);
            
            Vt = this.temperatureConstant;
            noStages = this.numberOfStages;
            
            ys = zeros(1,noStages);  % Ladder filter stages

            y = zeros(size(x));      % Filter output;

            for( c = 1:numberOfChannels )
                
                for( n = 1:N )

                    g = 1 - exp(-2*pi*FcN(n)/2);

                    stageInput = x(n,c) - 4*r(n)*ys(noStages);   % Input signal and feedback from last stage

                    for( k = 1:noStages )

                        ys(k) = ys(k) + 2*Vt*g*( tanh(stageInput/(2*Vt)) - tanh(ys(k)/(2*Vt)) );

                        stageInput = ys(k);

                    end;

                    y(n,c) = ys(noStages);
                    
                end;
                
            end;
            
            this.output.write( y );
            
        end;
        
    end
end