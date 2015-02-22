clear classes;
clc;
close all

fs = 44100;

osc1 = AliasFreeSawtoothOscillator('Osc 1');
osc2 = AliasFreeSawtoothOscillator('Osc 2');
mixer = Mixer('Mixer', 2);
reverb = Reverb('Reverb', fs);
lpf = TwoPoleFilter('Filter');
writer = WaveWriter('Writer');

mixer.channels(1).input.connect(osc1.output);
mixer.channels(2).input.connect(osc2.output);
lpf.input.connect(mixer.sendOutput);
%reverb.input.connect(mixer.sendOutput);
mixer.returnInput.connect(lpf.output);
writer.input.connect(mixer.mainOutput);

osc1.frequencyInput.set(55);
osc2.frequencyInput.set(165);

mixer.channels(1).lowShelfEq.gainInput.set(2);
mixer.channels(1).lowShelfEq.frequencyInput.set(0.01);
mixer.channels(1).levelInput.set(0*0.5);

mixer.channels(2).highShelfEq.gainInput.set(2);
mixer.channels(2).highShelfEq.frequencyInput.set(0.4);
mixer.channels(2).levelInput.set(0*0.5);
mixer.channels(2).sendLevelInput.set(0.5);

lpf.frequencyInput.set(0.01);
%reverb.mix = 0.1;

writer.update(44100);
