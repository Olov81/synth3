classdef MultiOscillator < Module
    
    properties (SetAccess = private)
       
        frequencyInput
        pulseWidthInput
        output
        
    end
    
    properties
        
        waveform
        detune
        stereospread
        voices
        tuning
        
    end
    
    methods
        
        function this = MultiOscillator(name)
            
            this = this@Module(name);
            
            this.frequencyInput = this.createInputPort();
            this.pulseWidthInput = this.createInputPort();
            this.output = this.createOutputPort();

            this.waveform = 'sawtooth';
            this.detune = 0.1;
            this.stereospread = 0.5;
            this.voices = 4;
            this.tuning = 0;
            
        end;
        
        function y = doUpdate(this, N)
            
            if( this.voices == 1 )
                spread = 0.5;
            else
                spread = (0:this.voices-1)/(this.voices-1);
            end;
            
          	detuning = (spread-0.5)*this.detune;
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
            pulseWidth = this.pulseWidthInput.read(N);
            
            y = zeros(N,2);
            
            for( n = 1:this.voices )
                
                f = frequency*2^((detuning(n)+this.tuning)/12);
                
                f = max(f, 1);
                
                if(strcmp(this.waveform, 'squarewave'))
                    wave = MexAliasFreeSquare(N, f, phase(n), pulseWidth);
                else
                    wave = MexAliasFreeSaw(N, f, phase(n));
                end;
                
                y(:,1) = y(:,1) + 2*pan(n)*wave;
                y(:,2) = y(:,2) + 2*(1-pan(n))*wave;
                
            end;
           
            this.output.write( y );
          
        end
        
    end
    
end
                
                
        
        
        
        
        