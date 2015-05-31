function events = TestNoteStringParser

keyset = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
valueset = [-9, -7, -5, -4, -2, 0, 2];
notetable = containers.Map(keyset, valueset);

phrase = ['F8 -8 Ab8  -16 F8 F16 Bb8   F8   Eb8 '...
          'F8 -8 C8+1 -16 F8 F16 Db8+1 C8+1 Ab8 '];

symbols = textscan(phrase, '%s');
symbols = symbols{1};
numberOfSymbols = length(symbols);
events = cell(numberOfSymbols,1);

startMeasure = 0;
numberOfNotes = 0;

for n = 1:numberOfSymbols
    
    symbol = symbols{n};
    
    if( notetable.isKey(symbol(1)))
        [note, eventLength] = parseNote(symbol, notetable);
        event.note = note;
        event.length = eventLength;
        event.start = startMeasure;
        event.velocity = 1; % TODO
        events{numberOfNotes+1} = event;
        numberOfNotes = numberOfNotes + 1;
    elseif( symbol(1) == '-' )
        eventLength = parseRest(symbol);
    end;
    
    startMeasure = startMeasure + eventLength;
end

events = events(1:numberOfNotes);

end

function [note, notelength] = parseNote(symbol, notetable)

    note = notetable(symbol(1));
    
    symbol = symbol(2:end);
    
    if( symbol(1) == '#')
        note = note + 1;
        symbol = symbol(2:end);
    elseif( symbol(1) == 'b')
        note = note - 1;
        symbol = symbol(2:end);
    end;
    
    [notelengthStr, octaveStr] = strtok(symbol, '+-');
    
    notelength = 1/str2double(notelengthStr);
    octave = str2double(octaveStr);
    
    if( strfind(symbol, '+') )
        note = note + 12*octave;
    elseif( strfind(symbol, '-') )
        note = note - 12*octave;
    end;
   
end

function restLength = parseRest(symbol)

    restLength = 1/str2double(symbol(2:end));
    
end