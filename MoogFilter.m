classdef MoogFilter < Module
   
    properties
        
        numberOfStages
        temperatureConstant
        
        input
        cutoffFrequencyInput
        resonanceInput
        
        output
        
    end
    
    methods
        
        function this = MoogFilter(name, numberOfStages)
    
            this = this@Module(name);
            this.numberOfStages = numberOfStages;
            this.temperatureConstant = 1;
                        
            this.cutoffFrequencyInput = this.createInputPort( 0.5 );
            this.input = this.createInputPort;
            this.resonanceInput = this.createInputPort( 0.1 );

            this.output = this.createOutputPort();
            
        end;
        
        function doUpdate(this, N)
            
            x = this.input.read(N);
            FcN = this.cutoffFrequencyInput.read(N);
            r = this.resonanceInput.read(N);
            
            Vt = this.temperatureConstant;
            noStages = this.numberOfStages;
            
            ys = zeros(1,noStages);  % Ladder filter stages

            y = zeros(size(x));      % Filter output;

            for( n = 1:N )

                g = 1 - exp(-2*pi*FcN(n)/2);

                stageInput = x(n) - 4*r(n)*ys(noStages);   % Input signal and feedback from last stage

                for( k = 1:noStages )

                    ys(k) = ys(k) + 2*Vt*g*( tanh(stageInput/(2*Vt)) - tanh(ys(k)/(2*Vt)) );

                    stageInput = ys(k);

                end;

                y(n) = ys(noStages);

            end;
            
            this.output.write( y );
            
        end;
        
    end
end