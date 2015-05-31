% Non-linear Moog filter discrete approximation
% Syntax: y = moogFilter(x,FcN,r,noStages,Vt)
%
% y         - output signal
% x         - input signal
% FcN       - normalized cutoff freqency Fc/(Fs/2), where
%           Fc is the desired cutoff frequency in Hz and
%           Fs is the sample rate. Interval: (0-1]
% r         - resonance. Typical interval: [0-1)
% noStages  - number of ladder stages, approximiatly corresponding 
%           to filter order. Default: 4
% Vt        - thermal voltage, affects the amplification. Default: 1
function y = moogFilterFunction(x,FcN,r,noStages,Vt)

if( ~exist('noStages','var'))
    noStages = 4;
end;
if( ~exist('Vt','var'))
    Vt = 1;
end;

if( length(FcN) == 1)
    FcN = FcN*ones(size(x));
end;
if( length(r) == 1)
    r = r*ones(size(x));
end;

ys = zeros(1,noStages);  % Ladder filter stages

y = zeros(size(x));      % Filter output;

for( n = 1:length(x) )

    g = 1 - exp(-2*pi*FcN(n)/2);

    stageInput = x(n) - 4*r(n)*ys(noStages);   % Input signal and feedback from last stage
    
    for( k = 1:noStages )

        ys(k) = ys(k) + 2*Vt*g*( tanh(stageInput/(2*Vt)) - tanh(ys(k)/(2*Vt)) );

        stageInput = ys(k);
        
    end;
   
    y(n) = ys(noStages);

end;
