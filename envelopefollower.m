function output = envelopefollower(input,attack,release,lookahead)

if( ~exist('lookahead') )
    lookahead = 0;
end;

desired_signal = [abs(input); zeros(lookahead,1)];

output = zeros(size(input));

currentamplitude = desired_signal(1);

inputlength = length(input);

for(n = 1:inputlength)
    
    output(n) = currentamplitude;
    
    envelopesample = desired_signal(n + lookahead);
    
    if(currentamplitude < envelopesample)
        amplitudechange = (envelopesample-currentamplitude)/release;
    else
        amplitudechange = (envelopesample-currentamplitude)/attack;
    end;
    
    currentamplitude = currentamplitude + amplitudechange;
    
end;