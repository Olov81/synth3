function [cv,gate] = TestPolyphonicSequncer2(events)

    fs = 44100;
    bpm = 120;
    numberOfVoices = 2;
    wholeNoteTime = 1/(bpm/4)*60;
    T = 5;
    N = T*fs;
    
	cv = zeros(N, numberOfVoices);
    gate = zeros(N, numberOfVoices);
    numberOfEvents = length(events);
    t = 0;
    
    for( n = 1:N )
    
        
    end;
    
end