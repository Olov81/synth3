classdef MultiTapDelay < AudioEffect
   
    properties
    
        tap1Delay
        tap2Delay
        feedback
        
    end
    
    properties(SetAccess = private)
        
        wetmixInput
        
    end
    
    properties(Access = private)
       
        delayBufferX
        delayBufferY
        fs
        buffersize
    end
    
    methods
       
        function this = MultiTapDelay(name, fs)
        
            this = this@AudioEffect(name);
            
            this.wetmixInput = this.createInputPort();
            
            this.buffersize = 2*fs;
            this.delayBufferX = zeros( this.buffersize, 1 );
            this.delayBufferY = zeros( this.buffersize, 1 );
            
            this.tap1Delay = round(fs*0.4);
            this.tap2Delay = round(fs*0.4);
            this.feedback = 0.5;
        end
        
        function updateFx(this, N)
            
            x = this.input.read(N);
            dry = x;
            x = sum(x,2);
            
            y1 = zeros(N,1);
            y2 = zeros(N,1);
            
            index = 1;
            
            for( n = 1:N )
                
                index1 = mod(index-this.tap1Delay, this.buffersize) + 1;
                index2 = mod(index1-this.tap2Delay, this.buffersize) + 1;
                
                this.delayBufferX(index) = x(n);
                
                y1(n) = this.delayBufferX(index1) - this.feedback*this.delayBufferY(index1);
                y2(n) = this.delayBufferX(index2) - this.feedback*this.delayBufferY(index2);
                
                this.delayBufferY(index) = y2(n);
                
                index = mod(index, this.buffersize) + 1;
            end
            
            mix = this.wetmixInput.read(N);
            
            wet = multiplysignals([y1, y2],mix);
            dry = multiplysignals(dry, (1-mix));
            
            this.output.write(mixsignals(wet, dry));

        end
    end
end