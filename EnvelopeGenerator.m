classdef EnvelopeGenerator
    properties
        m_fs;
        m_attack;
        m_decay;
        m_sustain;
        m_release;
        m_k;
        m_gateAmplitudeSensitivy;
    end
    methods
        
        function this = EnvelopeGenerator(fs)
            
            this.m_fs = fs;
            this.m_attack = 1e-3;
            this.m_decay = 0.5;
            this.m_sustain = 0;
            this.m_release = 0.2;
            this.m_k = log(0.7);
            this.m_gateAmplitudeSensitivy = 0;
            
        end
        
        function y = update(this, gate)
            
            Ts = 1/this.m_fs;

            y = zeros(size(gate));
            state = 0;
            t = 0;
            yR = 0;
            oldGate = 0;
            thresh = 1e-7; % Envelope doesn't react to slopes smaller than this
            currentValue = 0;
            peakValue = 0;
            velSens = this.m_gateAmplitudeSensitivy;
            A = makeLengthEqualTo( this.m_attack, gate);
            D = makeLengthEqualTo( this.m_decay, gate);
            S = makeLengthEqualTo( this.m_sustain, gate);
            R = makeLengthEqualTo( this.m_release, gate);
            k = this.m_k;
            
            for n = 1:length(gate)

                slope = (gate(n) - oldGate)*Ts;

                if( slope > thresh) % positive slope, restart envelope
                    peakValue = velSens*gate(n) + (1-velSens);
                    state = 1;
                    % We want to restart from the current value, not from zero,
                    % to avoid clicks
                    t = A(n)*log(1-currentValue/peakValue*(1-exp(k)))/k;
                elseif( state == 1 && slope < -thresh) % negative slope, release phase
                    state = 0;
                    yR = y(n-1);    % Output value at start of release phase
                    t = 0;
                end;

                if(state == 1)

                    if(t < A(n))    % Attack phase

                        y(n) = peakValue*(1-exp(k*t/A(n)))/(1-exp(k));

                    else            % Decay phase

                        y(n) = S(n) + (peakValue-S(n))*exp((t-A(n))*k/D(n));

                    end;

                else                % Release phase

                    y(n) = yR*exp(k*t/R(n));

                end;

                t = t + Ts;

                oldGate = gate(n);

                currentValue = y(n);
            end;
        end
    end
end