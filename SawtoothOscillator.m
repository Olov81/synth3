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
        
        function doUpdate(this, N)
           
            freq = this.frequencyInput.read(N);
            sync = this.syncInput.read(N);
            phaseshift = this.phaseshiftInput.read(N);
            
            oldSync = 0;
            phase = 0;
            fs = this.fs;
            y = zeros(size(freq));

            
            for( n = 1:N )
                
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
    