classdef MatrixSequencer < Module
   
    properties
        
        pattern
        bpm
        beatValue
        shuffle
        resolution
        tuning
        transpose
        loop
        
        gateOutput
        cvOutput
        
    end
    
    properties(Access=private)
        fs
    end
    
    methods
       
        function this = MatrixSequencer(name, fs)
            
            this = this@Module(name);
            this.fs = fs;
            this.pattern = 0;
            this.bpm = 120;
            this.beatValue = 4;
            this.shuffle = 0;
            this.resolution = 16;
            this.tuning = 440;
            this.transpose = 0;
            this.loop = false;
            this.pattern = [[0 0 12 12  0 0 12 12  0 0 12 12  0 0 12 12] - 36;
                            1 1  1  1  1 1  1  1  1 1  1  1  1 1  1  1;
                            [1 1  1  1  1 1  1  1  1 1  1  1  1 1  1  1]/2];
                        
            this.gateOutput = this.createOutputPort();
            this.cvOutput = this.createOutputPort();
            
        end;
        
        function doUpdate(this, N)
                       
            dim = size(this.pattern);
            patternlength = dim(2)/this.resolution;
            
            noteLength = round((this.beatValue/this.resolution)*60/this.bpm*this.fs);
            T = noteLength*patternlength*this.resolution;

            pitch = this.pattern(1,:) + this.transpose;
            velocity = this.pattern(2,:);
            noteduration = this.pattern(3,:);
                
            gate = zeros(T,1);
            gate(1:2*noteLength:T) = velocity(1:2:end);
            gate(noteLength + round(this.shuffle*noteLength):2*noteLength:end) = velocity(2:2:end);

            a = noteLength*noteduration;
            b = 1:noteLength:length(gate);
            index = floor(a + b);
            gate(index) = -velocity;
            gate = cumsum(gate);

            CV = ones(noteLength,1)*(this.tuning*2.^(pitch/12));
            CV = CV(:);
            
            gate = min(gate, 1);
            
            if(this.loop)
                repeats = ceil(N/T);
                CV = CV*ones(1, repeats);
                CV = CV(:);
                gate = gate*ones(1, repeats);
                gate = gate(:);
            end;
            
            this.gateOutput.write( gate );
            this.cvOutput.write( CV );
            
        end;
    end
end