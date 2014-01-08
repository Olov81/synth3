classdef MultiOscillator < Module
    
    properties (SetAccess = private)
       
        frequencyInput
        
        leftOutput
        rightOutput
        
    end
    
    properties
        
        detune
        stereospread
        voices
        
    end
    
    methods
        
        function this = MultiOscillator(name)
            
            this = this@Module(name);
            
            this.frequencyInput = this.createInputPort();
            this.leftOutput = this.createOutputPort();
            this.rightOutput = this.createOutputPort();
            
            this.detune = 0.1;
            this.stereospread = 0.5;
            this.voices = 4;
            
            
        end;
        
        function y = doUpdate(this, N)
                        
            if( this.voices == 1 )
                spread = 0.5;
            else
                spread = (0:this.voices-1)/(this.voices-1);
            end;
            
          	tuning = (spread-0.5)*this.detune;
            phase = rand(this.voices,1);
            
            pan = this.stereospread*(spread - 0.5) + 0.5;
            
            for( n = 1:length(pan) )
                if( pan(n) > 1 )
                    pan(n) = 1;
                elseif( pan(n) < 0 )
                    pan(n) = 0;
                end;
            end;
            
            frequency = this.frequencyInput.read(N);
            
            y = zeros(N,2);
            
            for( n = 1:this.voices )
                
                f = frequency*2^(tuning(n)/12);
                
                output = MexAliasFreeSaw(N, f, phase(n));
                
                y(:,1) = y(:,1) + pan(n)*output;
                y(:,2) = y(:,2) + (1-pan(n))*output;
                
            end;
           
            this.leftOutput.write( y(:,1) );
            this.rightOutput.write( y(:,2) );
            
        end
        
    end
    
end
                
                
        
        
        
        
        