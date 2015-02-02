classdef Compressor < AudioEffect
   
    properties
        
        fs
        threshold
        ratio
        attack
        release
        useSidechainInput
    end
    
    properties(SetAccess = private)
        
        sidechainInput
        gainOutput
    end
    
    methods
        
        function this = Compressor(name, fs)
           
            this = this@AudioEffect(name);
            
            this.sidechainInput = this.createInputPort();
            this.gainOutput = this.createOutputPort();
            
            this.fs = fs;
            this.threshold = 0.1;
            this.ratio = 0.5;
            this.attack = 0.05;
            this.release = 0.2;
            this.useSidechainInput = false;
            
        end
        
        function updateFx(this, N)
            
            amplitude_function =...
                [0 0;...
                this.threshold this.threshold;...
                1 this.threshold+this.ratio];

            x = this.input.read(N);
            
            if( this.useSidechainInput )
                sidechain = this.sidechainInput.read(N);
            else
                sidechain = x;
            end;
            
            [output, gain] = dynamics(x,...
                                      sidechain,...
                                      amplitude_function,...
                                      this.attack*this.fs,...
                                      this.release*this.fs,...
                                      0);
                                  
            this.output.write(output);
            this.gainOutput.write(gain);
        end
    end    
end