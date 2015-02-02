function output = fastFilter(B,A,x)

dimA = size(A);
dimB = size(B);

dimx = size(x);

no_channels = dimx(2);

inputLength = length(x);

if( dimA(1) == 1 )
    
    A = ones(inputLength,1)*A;
    
end;

if( dimB(1) == 1 )
    
    B = ones(inputLength,1)*B;
    
end;

a0 = A(:,1);
A = A(:,2:end);

dimA = size(A);
dimB = size(B);

dl_length = dimB(2);

if( dimA(2) < dimB(2) )
        
    A = [A zeros(inputLength, dimB(2)-dimA(2))];
    
    dl_length = dimB(2);
    
elseif( dimA(2) > dimB(2) )
    
    B = [B zeros(inputLength, dimA(2)-dimB(2))];
    
    dl_length = dimA(2);
    
end;

output = zeros(size(x));

for( ch = 1:no_channels )
    
    dl_x = zeros(dl_length,1);
    dl_y = zeros(dl_length,1);
    dl_index = 1;
    y = 0;
    
    for( n = 1:inputLength )

        dl_x(dl_index) = x(n,ch);
        dl_y(dl_index) = y;

        dl_index = mod(dl_index, dl_length) + 1;
        
        y = 0;

        for( m = 0:dl_length-1 )

            index = mod(dl_index + m - 1, dl_length) + 1;

            coeff_index = dl_length - m;

            y = y + B(n, coeff_index)*dl_x(index) - A(n, coeff_index)*dl_y(index);

        end;

        y = y/a0(n);

        output(n, ch) = y;
        
    end;
    
end;