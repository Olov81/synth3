
close all;
clear osc;

osc = MultiOscillator('VCO');

osc.frequencyInput.set(3000);

osc.voices = 1;
osc.stereospread = 0;

osc.update(44100*30);

plot(osc.output.data(:,1));