function y = tableinterpolate(x, table)

y = zeros(size(x));
for( n = 1:length(table)-1 )
   
    i1 = n;
    i2 = n+1;
    
    x1 = table(i1,1);
    x2 = table(i2,1);
    
    y1 = table(i1,2);
    y2 = table(i2,2);
    
    index = find( x >= x1 & x < x2 );
    
    y(index) = x(index)*((y2-y1)/(x2-x1));
    
end;