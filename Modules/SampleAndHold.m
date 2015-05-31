classdef SampleAndHold < AudioEffect
   
    properties
       decimationInput
       mix
    end
    
    methods
       
        function this = SampleAndHold(name)
        
            this = this@AudioEffect(name);
            this.decimationInput = this.createInputPort();
            mix = 1;
            
        end
        
        function updateFx(this, N)
            
            decimation = this.decimationInput.read(N);
            x = this.input.read(N);
            
            step = 1./decimation;

            index = 1;

            y = zeros(size(x));
            
            for n = 1:length(x)

                y(n,:) = x(index,:);

                nextIndex = index + step(n);

                if( n > nextIndex )
                    index = floor(nextIndex);
                    if( index > length(x) )
                        index = length(x);
                    end;
                end;
            end
    
            y = this.mix*y + (1-this.mix)*x;
            this.output.write(y);
            
        end
    end
end