classdef EnvelopeFollower < AudioEffect
   
    properties
        
        fs
        attack
        release
    end
    
    properties(SetAccess = private)
        
    end
    
    methods
        
        function this = EnvelopeFollower(name, fs)
           
            this = this@AudioEffect(name);
            
            this.fs = fs;
            this.ratio = 0.5;
            this.attack = 0.05;
            
        end
        
        function updateFx(this, N)
                        
            x = this.input.read(N);
            
            desired_signal = abs(x);

            output = zeros(size(input));

            currentamplitude = desired_signal(1);

            for(n = 1:N)

                output(n) = currentamplitude;

                envelopesample = desired_signal(n);

                if(currentamplitude < envelopesample)
                    amplitudechange = (envelopesample-currentamplitude)/this.release;
                else
                    amplitudechange = (envelopesample-currentamplitude)/this.attack;
                end;

                currentamplitude = currentamplitude + amplitudechange;

            end;
            
            this.output.write(output);
        end
    end    
end