classdef Reverb < AudioEffect
   
    properties
       
        fs
        mix
        time
        width
        initialDelay
        hfFallOffRate
        
    end
    
    methods
        
        function this = Reverb(name, fs)
           
            this = this@AudioEffect(name);
            
            this.fs = fs;
            this.mix = 0.01;
            this.time = 1.0;
            this.width = 0.8;
            this.initialDelay = 0.2;
            this.hfFallOffRate = 0.9;
        end
        
        function updateFx(this, N)
           
            x = this.input.read(N);
            monoInput = sum(x,2);
            
            ir = CreateImpulseResponse(...
                this.fs,...
                this.time,...
                this.width,...
                this.initialDelay,...
                this.hfFallOffRate);
                
            wetR = fconv(ir(:,1),monoInput);
            wetL = fconv(ir(:,2),monoInput);

            wet = [wetL(:) wetR(:)];

            y = mixsignals(this.mix*wet, (1-this.mix)*x);

            this.output.write( y );
            
        end
    end    
end

function y = CreateImpulseResponse(fs, time, width, initialDelay, hfFallOffRate)

    width = width/2 + 0.5;
    timeSamples = (0:time*fs)'/fs;

	noise = rand(size(timeSamples))-0.5;
    noise = noise/sum(noise);
    noise(find(noise > 1)) = 1;
    irL = noise;
    irR = flipud(irL);
    
    
	freq = exp(-timeSamples*hfFallOffRate);
	resonance = 0;
    temperatureConstant = 1.0;
    filterOrder = 4;
    irL = moogFilterFunction(irL, freq, resonance, filterOrder, temperatureConstant );
	irR = moogFilterFunction(irR, freq, resonance, filterOrder, temperatureConstant );
    decayConstant = 0.2;
    hR = [zeros(initialDelay*fs,1); irR.*exp(-timeSamples/(decayConstant*time))];
    hL = [zeros(initialDelay*fs,1); irL.*exp(-timeSamples/(decayConstant*time))];
    
    hR = hR/max(abs(hR));
    hL = hL/max(abs(hL));

    wetR = (1-width).*hL + width.*hR;
    wetL = (1-width).*hR + width.*hL;

    y = [wetR wetL];
end