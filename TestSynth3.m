clear classes;

fs = 44100;

osc = SawtoothOscillator(fs);
mosc = MultiOscillator(osc);
vcf = MoogFilter(4);

vcf.cutoffFrequency = 0.5;
vcf.resonance = 0.5;

mosc.frequency = 0*10*( 1 + sin(2*pi*7*(0:5*fs-1)'/fs) ) +70;
mosc.detune = 0.01;
mosc.voices = 8;
mosc.stereospread = .2;

% mosc.syncInput = sin(2*pi*120*(0:fs-1)'/fs);

y = mosc.update();
y = processStereo(y, vcf);

sound(y, fs);