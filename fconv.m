function y = fconv(h,x,y)
% FCONV FFT-based convolution
%     y = FCONV(A,B) performs convolution of column vectors A and B
if length(h)>length(x)
    temp = h;
    h = x;
    x = temp;
end;

NF = length(h);
N = 2^ceil(log2(NF));
lenx = length(x);
M = ceil(lenx/N);
x = [x; zeros(M*N-lenx,1)];
H = fft(h,2*N);
y = zeros(lenx+2*N,1);

for n=0:M-1
    xn = x(n*N+1:n*N+N);    
    Xn = fft(xn,2*N);
    Yn = Xn.*H;
    yn = real(ifft(Yn));
    y(n*N+1:n*N+2*N) = yn + y(n*N+1:n*N+2*N);
end;
y = y(1:lenx+NF-1);


