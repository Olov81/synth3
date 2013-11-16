classdef EnvelopeGenerator < Module
    
    properties
        gateInput;
        attackInput;
        decayInput;
        sustainInput;
        releaseInput;
        output;
    end
    
    properties(Access = private)
        fs
        rate
    end
    
    methods
        
        function this = EnvelopeGenerator(name, fs)
            
            this = this@Module(name);
            
            this.fs = fs;
            this.rate = log(0.7);
            
            this.gateInput = this.createInputPort();
            this.attackInput = this.createInputPort();
            this.decayInput = this.createInputPort();
            this.sustainInput = this.createInputPort();
            this.releaseInput = this.createInputPort();
           
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this, N)
            
            Ts = 1/this.fs;

            y = zeros(N,1);
            state = 0;
            t = 0;
            yR = 0;
            oldGate = 0;
            thresh = 1e-7; % Envelope doesn't react to slopes smaller than this
            currentValue = 0;
            
            A = this.attackInput.read(N);
            D = this.decayInput.read(N);
            S = this.sustainInput.read(N);
            R = this.releaseInput.read(N);
            k = this.rate;
            gate = this.gateInput.read(N);
            
            for n = 1:N

                slope = (gate(n) - oldGate)*Ts;

                if( slope > thresh) % positive slope, restart envelope
                    state = 1;
                    % We want to restart from the current value, not from zero,
                    % to avoid clicks
                    t = A(n)*log(1-currentValue*(1-exp(k)))/k;
                elseif( state == 1 && slope < -thresh) % negative slope, release phase
                    state = 0;
                    yR = y(n-1);    % Output value at start of release phase
                    t = 0;
                end;

                if(state == 1)

                    if(t < A(n))    % Attack phase

                        y(n) = (1-exp(k*t/A(n)))/(1-exp(k));

                    else            % Decay phase

                        y(n) = S(n) + (1-S(n))*exp((t-A(n))*k/D(n));

                    end;

                else                % Release phase

                    y(n) = yR*exp(k*t/R(n));

                end;

                t = t + Ts;

                oldGate = gate(n);

                currentValue = y(n);
            end;
            
            this.output.write( y );
        end;
    end
end