function [output, gain] = dynamics(input,...
                                   sidechain,...
                                   amplitude_function,...
                                   attack,...
                                   release,...
                                   lookahead)

dim_sidechain = size(sidechain);

if( dim_sidechain(2) == 2 )
    sidechain = mixsignals(sidechain(:,1),sidechain(:,2));
end;

sidechain_amplitude = abs(sidechain) + eps;

desired_amplitude = tableinterpolate(sidechain_amplitude, amplitude_function);

desired_gain = desired_amplitude./(sidechain_amplitude);

if( ~exist('lookahead') )
    lookahead = 0;
end;

gain = envelopefollower(desired_gain, attack, release, lookahead);

output = zeros(size(input));

dim_input = size(input);

for n = 1:dim_input(2)
    output(:,n) = gain.*input(:,n);
end;
