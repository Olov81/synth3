function y = processStereo( x, effect )

dim = size(x);

y = zeros(size(x));

for( n = 1:dim(2) )

    y(:,n) = effect.update(x(:,n));

end;