function y = multiplysignals(x,scalars)

    y = zeros(size(x));
    dimx = size(x);

    for c = 1:dimx(2)
        y(:,c) = scalars.*x(:,c);
    end;
end
