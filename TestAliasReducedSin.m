scale = 1000;

fs = 44100/scale;
ts = 1/fs;
N = 6;
T = 8*scale;
t = (0:T*fs-1)/fs;
f = 80000*(1:length(t))/length(t) + 1;
% f = 3000 + 2500*sin(2*pi*2*t/scale);
% f = 500*ones(size(t));
f = f/scale;

% [b, a] = ellip(N, 1, 60, 2*pi*fs/2, 'low', 's');
[b, a] = butter(N, 2*pi*fs/10, 'low', 's');

[A,B,C,D] = tf2ss(b, a);

[P, LAMBDA] = eig(A);

C_ = C*P;
B_ = P\B;
lambda = diag(LAMBDA);

y = zeros(size(t));
w = zeros(N,1);

t = 0;

c1 = exp(lambda*ts);
c2 = B_./(lambda.^2);

usave = zeros(size(t));
ISave = zeros(N,length(t));

u = zeros(size(t));

tic
for( n = 1:length(y) )
    
    T = 1/f(n);
    
    t0 = t;
    t = t + ts;
    
    k = 2*pi*f(n);
    
    I = -lambda*sin(k*t) + c1.*(lambda*sin(k*t0) + k*cos(k*t0)) - k*cos(k*t);
    
    I = I./(k^2 + lambda.^2);
    
    w = c1.*w + B_.*I;   
   
    out = real(C_*w);
    
    y(n) = out;
    
end;
toc

y = 2*y - 1;

plot(y)



