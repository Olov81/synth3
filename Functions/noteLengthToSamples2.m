function n = noteLengthToSamples2(noteLength, bpm, fs)

beatsPerSecond = bpm/(4*60);

n = round(noteLength*fs/beatsPerSecond);