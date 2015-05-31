function [cv, gate] = TestPolyphonicSequencer(events)

    fs = 44100;
    bpm = 120;
    numberOfVoices = 2;
    wholeNoteTime = 1/(bpm/4)*60;
    T = 5;
    N = T*fs;
    
    cv = zeros(N, numberOfVoices);
    gate = zeros(N, numberOfVoices);
    numberOfEvents = length(events);
    voiceIndex = 1;
    
    for( n = 1:numberOfEvents );
    
        event = events{n};
        
        startN = floor(event.start*wholeNoteTime*fs) + 1;
        lengthN = floor(event.length*wholeNoteTime*fs) + 1;
        endN = startN + lengthN;
        
        if(startN > N || endN > N)
            break;
        end;
        
        gate(startN:endN, voiceIndex) = 1;
        cv(startN:endN, voiceIndex) = 440*2^(event.note/12);
        
        voiceIndex = voiceIndex + 1;
        
        if( voiceIndex > numberOfVoices )
            voiceIndex = 1;
        end;
    end;
end