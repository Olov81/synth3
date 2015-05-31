classdef Chorus < AudioEffect
   
    properties
       
        fs
        mix,
        amplitude,
        frequency,
        phaseDifference
        leftDelay
        rightDelay
    end
    
    methods
        
        function this = Chorus(name, fs)
           
            this = this@AudioEffect(name);
            
            this.fs = fs;
            this.mix = 0.5;
            this.amplitude = 100;
            this.frequency = 1.0;
            this.phaseDifference = pi;
            this.leftDelay = 0.05*fs;
            this.rightDelay = 0.0*fs;
        end
        
        function updateFx(this, N)
           
            x = this.input.read(N);
            monoInput = sum(x,2);
            A = this.amplitude;
            
            t = (0:N-1)/this.fs;
            
            lfo = (sin(this.frequency*pi*t) + 1)*A/2 + 1;
            lfoL = lfo + this.leftDelay;
            lfoR = lfo + this.rightDelay;
            
            wet = zeros(N,2);

            bufferLength = ceil(max(this.leftDelay,this.rightDelay)+A+2);
            
            delayLine = zeros(1,bufferLength); %Safety margin 2

            k = 1;

            for n = 1:length(t)

                delayLine(k) = monoInput(n);

                %Calculate desired delay
                delay = lfoL(n);
                delayR = lfoR(n);
                
                %Interpolate
                index = floor(delay);
                indexR = floor(delayR);

                interpFactor = delay - index;
                interpFactorR = delayR - indexR;

                s1 = delayLine(mod(k+index,bufferLength)+1);
                s2 = delayLine(mod(k+index+1,bufferLength)+1);

                s1R = delayLine(mod(k+indexR,bufferLength)+1);
                s2R = delayLine(mod(k+indexR+1,bufferLength)+1);

                wet(n,1) = (1-interpFactor)*s1 + interpFactor*s2;
                wet(n,2) = (1-interpFactorR)*s1R + interpFactorR*s2R;

                k = mod(k,bufferLength)+1;

            end;

            y = mixsignals(this.mix*wet, (1-this.mix)*x);

            this.output.write( y );
            
        end
    end    
end