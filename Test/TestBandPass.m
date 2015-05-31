close all;

fs = 44100;
Ts = 1/fs;
T = 1;
t = (0:T*fs-1)'/fs;
f = 110;
x = sawtooth(2*pi*f*t);
Q = 0.5;
dw = 100;
wc = 3000;
fw = 2*dw/(pi*fs);
fc = 2*wc/(pi*fs);
R2C2 = 1;

z = tf('z',Ts);
s = tf('s');
G = dw*s/(s^2 + dw*s + wc^2);
% G = (-wc^2*R2C2*s)/(s^2 + s*(wc/Q) + wc^2);
Gd = (fw-fw*z^-2)/((1+fw+fc^2)+(2*fc^2-2)*z^-1+(1-fw+fc^2)*z^-2);
ltiview('bode',G);
% ltiview('bode',Gd);

% Gd = c2d(G, Ts, 'tustin');

% y = lsim(Gd,x,t);

% soundsc(0.2*y,fs)