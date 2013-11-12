classdef SawtoothOscillator < Module
    
    properties (SetAccess = private)
        fs
        frequencyInput
        syncInput
        phaseshiftInput
        waveformOutput
    end
    
    methods
        
        function this = SawtoothOscillator(fs)
            
            this.fs = fs;
            this.frequencyInput = this.createInputPort();
            this.syncInput = this.createInputPort();
            this.phaseshiftInput = this.createInputPort();
            this.waveformOutput = this.createOutputPort();
            
        end
        
        function doUpdate(this)
           
            freq = this.frequencyInput.read();
            sync = makeLengthEqualTo( this.syncInput.read(), freq );
            phaseshift = makeLengthEqualTo( this.phaseshiftInput.read(), freq );
            
            oldSync = 0;
            phase = 0;
            fs = this.fs;
            y = zeros(size(freq));

            
            for( n = 1:length(freq) )
                
                if( sync(n) > 0 && oldSync <= 0 )
                    phase = 0;
                end;
                oldSync = sync(n);
                
                phase = mod( phase + freq(n), fs );
                
                y(n) = 2*mod(phase/fs + phaseshift(n), 1)-1;
                
            end;
        
            this.waveformOutput.write( y );
            
        end;
        
    end 
end
    