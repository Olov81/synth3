function y = makeLengthEqualTo(x, reference)

    len_x = length(x);
    len_ref = length(reference);

    if( len_x >= len_ref )

        y = x(1:len_ref);

    else

        len_diff = len_ref - len_x;

        y = [x; x(end)*ones(len_diff,1)];

    end;
end