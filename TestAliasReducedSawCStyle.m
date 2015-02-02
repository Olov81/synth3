scale = 1000;

fs = 44100/scale;
ts = 1/fs;
N = 6;
T = 8*scale;
t = (0:T*fs-1)/fs;
f = 8000*(0:length(t)-1)/length(t) + 50;
% f = 3000 + 2500*sin(2*pi*2*t/scale);
% f = 100*ones(size(t));
f = f/scale;

[b, a] = ellip(N, 1, 60, 2*pi*fs/2, 'low', 's');
% [b, a] = butter(N, 2*pi*fs/3, 'low', 's');

[A,B,C,D] = tf2ss(b, a);

[P, LAMBDA] = eig(A);

C_ = C*P;
B_ = P\B;
lambda = diag(LAMBDA);

y = zeros(size(t));
w = zeros(N,1);
I = zeros(N,1);

t = 0;

c1 = exp(lambda*ts);
c2 = B_./(lambda.^2);

tic
for( n = 1:length(y) )
    
    T = 1/f(n);
    
    t0 = t;
    t = t + ts;
    
    k = f(n);
    
    y(n) = 0;
    
    if( t > T )
         
        for( m = 1:N )
            
            I(m) = (lambda(m)*t0 + 1)*exp(lambda(m)*(t-t0)) + (1 - exp(lambda(m)*(t-T)))*lambda(m)*T - lambda(m)*t - 1;
        
            w(m) = c1(m)*w(m) + k*c2(m)*I(m);
            
            y(n) = y(n) + real(C_(m)*w(m));
            
        end;
        
        t = t - T;
        
    else
        
        for( m = 1:N )
            
            I(m) = (lambda(m)*t0 + 1)*c1(m) - lambda(m)*t - 1;
            
            w(m) = c1(m)*w(m) + k*c2(m)*I(m);
            
            y(n) = y(n) + real(C_(m)*w(m));
            
        end;
        
    end;
    
end;
toc

y = 2*y - 1;

plot(y)



