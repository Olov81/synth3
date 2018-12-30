function y = resample2(x, factor)

dim = size(x);

if(dim(2) == 2)
    y = [resample2(x(:,1),factor) resample2(x(:,2), factor)];
    return;
end;
        
N = length(x);

t = 0;
K = floor(N/factor) - 1;
y = zeros(K,1);

% t = (0:factor:N)';
% pp = spline(0:N-1, x);
% y = ppval(pp, t);

for k = 1:K
   
   n = floor(t);
   
   interpfactor = t - n;
   
   y(k) = (1-interpfactor)*x(n+1) + interpfactor*x(n+2);
   
   t = t + factor;
   
end;

end

