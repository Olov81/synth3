close all;
s = tf('s');
fc = 1; %15000;
w0 = 2*pi*fc;
Zeta1 = 1;
Zeta2 = 1.5;
Zeta3 = 2;
Zeta4 = 2.5;
G1 = w0^2/(s^2 + 2*Zeta1*w0*s + w0^2);
G2 = w0^2/(s^2 + 2*Zeta2*w0*s + w0^2);
G3 = w0^2/(s^2 + 2*Zeta3*w0*s + w0^2);
G4 = w0^2/(s^2 + 2*Zeta4*w0*s + w0^2);
G = G1; %G1*G2*G3*G4;
num = get(G,'num');
den = get(G,'den');
[A, B, C, D] = tf2ss(num{1}, den{1});
eig(A)
bode(G);