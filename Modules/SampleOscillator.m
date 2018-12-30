classdef SampleOscillator < Module
    
    properties (SetAccess = private)
       
        output
        resampleFactorInput
        gateInput
    end
    
    properties
        loopStart
        loopEnd
        loopEnabled
    end
    
    properties(SetAccess = private)
        
        sample
        t
        decimationFactor
    end
    
    methods
        
        function this = SampleOscillator(name, sample, fs)
            
            this = this@Module(name);
            
            dim = size(sample);
            
            if(dim(2) ~= 2)
                sample = [sample(:,1) sample(:,1)];
            end;
            
            freqMagnitude = abs(fft(sample(:,1)));
            fundamental = find(freqMagnitude == max(freqMagnitude));
            this.decimationFactor = fs*fundamental(1)/dim(1);
            
            this.sample = sample;
            this.t = 0;
            this.loopStart = 0;
            this.loopEnd = 1;
            this.loopEnabled = 0;
            
            this.output = this.createOutputPort();
            this.gateInput = this.createInputPort();
            this.resampleFactorInput = this.createInputPort();
        end;
        
        function y = doUpdate(this, N)
            
            factor = this.resampleFactorInput.read(N)/this.decimationFactor;
            gate = this.gateInput.read(N);
            
            y = MexSamplePlayer(N, factor, this.sample, gate);
            
%             yL = updateMono(this, N, this.sample(:,1), factor, gate);
%             [yR, newt] = updateMono(this, N, this.sample(:,2), factor, gate);
%             this.t = newt;
%             y = [yL yR];
            this.output.write( y );
          
        end
        
        function [y, newt] = updateMono(this, N, x, factor, gate)
                        
            newt = this.t;
            
            sampleLength = length(x);
            lastGate = 0;
            
%             apa = ones(N, 1);
            
%             [B,A] = lpf12(0.1*apa, 1*apa);
            
            if(this.loopEnabled == 0)
               lpEnd = sampleLength - 2;
               lpStart = 0;
            else
                lpEnd = this.loopEnd;
                lpStart = this.loopStart;
            end;
            
            y = zeros(N, 1);
            
            for n = 1:N
                
                k = floor(newt);
   
                if(k > lpEnd)
                    y(n) = 0;
                else
                    interpfactor = newt - k;

                    y(n) = (1-interpfactor)*x(k+1) + interpfactor*x(k+2);
                end;
                
                newt = newt + factor(n);
   
                if(this.loopEnabled == 1 && newt > lpEnd)
                        newt = lpStart;
                end;
                
                if(gate(n) - lastGate > 0)
                    newt = 0;
                end;
                
                lastGate = gate(n);
            end;

        end
        
%         function [B,A] = lpf12(wc, q)
% 
%             wc = 2*pi*wc;
% 
%             a0 = 1 + 4*q./wc + 4./wc.^2;
%             a1 = (2 - 8./wc.^2);
%             a2 = (1 - 4*q./wc + 4./wc.^2);
% 
%             b0 = 1*ones(size(q));
%             b1 = 2*ones(size(q));
%             b2 = 1*ones(size(q));
% 
%             A = [a0 a1 a2];
%             B = [b0 b1 b2];
%         end
    end
    
end
                
                
        
        
        
        
        