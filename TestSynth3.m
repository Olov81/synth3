clear classes;

fs = 44100;
T = 3;
N = T*fs;
t = (0:N-1)/fs;

p1.time = 0.3;
p1.value = 0.8;
p2.time = 2;
p2.value = -0.3;
p3.time = 3;
p3.value = 1;

env = CustomEnvelope('CustomEnvelope', fs, [p1 p2 p3]);
writer = WaveWriter('Writer');

writer.input.connect(env.output);

writer.update(N);

plot(t, writer.y);
