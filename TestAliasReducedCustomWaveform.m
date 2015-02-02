scale = 1;

fs = 44100/scale;
ts = 1/fs;
N = 6;
T = 8*scale;
t = (0:T*fs-1)/fs;
f = 10000*(1:length(t))/length(t) + 1;
% f = 3000 + 2500*sin(2*pi*2*t/scale);
% f = 5*ones(size(t));
f = f/scale;

% [b, a] = ellip(N, 1, 60, 2*pi*fs/2, 'low', 's');
[b, a] = butter(N, 2*pi*fs/2, 'low', 's');

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

points = [0 0; 1 1];
dtmin = 1e-3;

% points = [0 1; 0.5-dtmin 1; 0.5 0; 1-dtmin 0];

index = 1;
numberOfPoints = length(points);
phase = 0;
nextPhase = 0;

tic
for( n = 1:length(y) )
    
    T = 1/f(n);
    
%     t0 = t;
%     t = t + ts;
    
    phase = phase + f(n)*ts;
        
    if( phase > nextPhase )
        
        nextIndex = mod(index, numberOfPoints) + 1;
        
        t1 = points(index,1);
        t2 = points(nextIndex,1);
        y1 = points(index,2);
        y2 = points(nextIndex,2);
        
        k = (y2-y1)/abs(t2-t1);
        
        index = nextIndex;
        
        if( nextIndex == 1 )
            
            nextPhase = 1;
            
        else
            
            nextPhase = t2;
            
        end;
        
    end;
    
    out = out + f(n)*k*ts;
    
    y(n) = out;
    
%     if( t > T )
%          
%         I = (lambda*t0 + 1).*exp(lambda*(t-t0)) + (1 - exp(lambda*(t-T))).*lambda*T - lambda*t - 1;
%         
%         t = t - T;
%         
%     else
%         
%         I = (lambda*t0 + 1).*c1 - lambda*t - 1;
%         
%     end;
%     
%     w = c1.*w + c2.*I;   
%    
%     out = real(C_*w);
%     
%     y(n) = out;
    
end;
toc

% y = 2*y - 1;

plot(y)



