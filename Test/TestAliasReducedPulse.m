scale = 100;

fs = 44100/scale;
ts = 1/fs;
N = 6;
T = 8*scale;
t = (0:T*fs-1)/fs;
f = 5000*(1:length(t))/length(t) + 1;
% f = 3000 + 2500*sin(2*pi*2*t/scale);
% f = 100*ones(size(t));
f = f/scale;

[b, a] = ellip(N, 1, 60, 2*pi*15000/scale, 'low', 's');
% [b, a] = butter(N, 2*pi*fs/2, 'low', 's');

[A,B,C,D] = tf2ss(b, a);

[P, LAMBDA] = eig(A);

C_ = C*P;
B_ = P\B;
lambda = diag(LAMBDA);

y = zeros(size(t));
u = zeros(size(t));
w = zeros(N,1);
wsave = zeros(N, length(t));
Isave = zeros(N, length(t));

pw = 0.5;
t = 0;

c1 = exp(lambda*ts);
c2 = B_./lambda;

tic
for( n = 1:length(y) )
    
    T = 1/f(n);
    
    t0 = t;
    t = t + ts;
    
	if( (t > pw*T) && (t0 < pw*T)  ) % high -> low
        
        I = exp(lambda*(t-t0)) - exp(lambda*(t-pw*T));
                
    elseif( t > T )                % low -> high
        
        t = t-T;
        
        I = exp(lambda*t) - 1;
                
    elseif( t < T*pw )               % high

        I = c1 - 1;
        
    else                            % low

        I = 0;
        
    end;
    
    w = c1.*w + c2.*I;   
   
    out = real(C_*w);
    
    y(n) = out;
    
end;
toc

y = 2*y - 1;

plot(y)



