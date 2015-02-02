function z = mixsignals(x,y)

xdim = size(x);
ydim = size(y);

if(xdim(2) > 2 | ydim(2) > 2)
    error('Only two columns allowed');
end;

if(xdim(2) > ydim(2))
    y = [y y];
end;
if(ydim(2) > xdim(2))
    x = [x x];
end;

xdim = size(x);
ydim = size(y);

if(xdim(1) > ydim(1))
    k = xdim(1)-ydim(1);
    y = [y; zeros(k,ydim(2))];
end;
if(ydim(1) > xdim(1))
    k = ydim(1)-xdim(1);
    x = [x; zeros(k,xdim(2))];
end;

z = x + y;