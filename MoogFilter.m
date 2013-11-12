classdef MoogFilter < Module
   
    properties
        
        numberOfStages
        temperatureConstant
        
        signalInput
        cutoffFrequencyInput
        resonanceInput
        
        signalOutput
        
    end
    
    methods
        
        function this = MoogFilter(numberOfStages)
    
            this.numberOfStages = numberOfStages;
            this.temperatureConstant = 1;
                        
            this.cutoffFrequencyInput = this.createInputPort;
            this.signalInput = this.createInputPort;
            this.resonanceInput = this.createInputPort;

            this.signalOutput = this.createOutputPort();
            
        end;
        
        function doUpdate(this)
            
            x = this.signalInput.read();
            FcN = makeLengthEqualTo( this.cutoffFrequencyInput.read(), x );
            r = makeLengthEqualTo( this.resonanceInput.read(), x );
            
            Vt = this.temperatureConstant;
            noStages = this.numberOfStages;
            
            ys = zeros(1,noStages);  % Ladder filter stages

            y = zeros(size(x));      % Filter output;

            for( n = 1:length(x) )

                g = 1 - exp(-2*pi*FcN(n)/2);

                stageInput = x(n) - 4*r(n)*ys(noStages);   % Input signal and feedback from last stage

                for( k = 1:noStages )

                    ys(k) = ys(k) + 2*Vt*g*( tanh(stageInput/(2*Vt)) - tanh(ys(k)/(2*Vt)) );

                    stageInput = ys(k);

                end;

                y(n) = ys(noStages);

            end;
            
            this.signalOutput.write( y );
            
        end;
        
    end
end