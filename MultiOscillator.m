classdef MultiOscillator
    
    properties (SetAccess = private)
        
        singleoscillator
        
    end
    
    properties
        
        frequency
        detune
        stereospread
        voices
        syncInput
    end
    
    methods
        
        function this = MultiOscillator(singleoscillator)
            
            this.singleoscillator = singleoscillator;
            this.frequency = singleoscillator.frequency;
            this.syncInput = singleoscillator.syncInput;
            this.detune = 0.1;
            this.stereospread = 0.5;
            this.voices = 4;
            
        end;
        
        function y = update(this)
            
            voices = this.voices;
            
            if( voices == 1 )
                spread = 0.5;
            else
                spread = (0:voices-1)/(voices-1);
            end;
            
          	tuning = 1 + 2*(spread-0.5)*this.detune;
            phase = 10*rand(size(tuning));
            
            pan = this.stereospread*(spread - 0.5) + 0.5;
            
            for( n = 1:length(pan) )
                if( pan(n) > 1 )
                    pan(n) = 1;
                elseif( pan(n) < 0 )
                    pan(n) = 0;
                end;
            end;
            
            frequency = this.frequency;
            osc = this.singleoscillator;
            
            osc.syncInput = this.syncInput;
            
            y = zeros(length(frequency),2);
            
            for( n = 1:voices )
                
                osc.frequency = frequency*tuning(n);
                osc.phaseshift = phase(n);
                
                output = osc.update();
                
                y(:,1) = y(:,1) + pan(n)*output;
                y(:,2) = y(:,2) + (1-pan(n))*output;
                
            end;
            
        end
        
    end
    
end
                
                
        
        
        
        
        