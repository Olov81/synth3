classdef TwoPoleFilter < AudioEffect
   
	properties
        frequencyInput
        resonanceInput
        type
    end
    
    methods
        
        function this = TwoPoleFilter(name)
            
            this = this@AudioEffect(name);
           
            this.frequencyInput = this.createInputPort();
            this.resonanceInput = this.createInputPort();
            
            this.type = 'lowpass';
            this.frequencyInput.set(0.1);
            this.resonanceInput.set(0.5);
        end
        
        function updateFx(this, N)
            
            wc = this.frequencyInput.read(N);
            q = this.resonanceInput.read(N);
            x = this.input.read(N);
            
            if( strcmp(this.type, 'highpass'))
                [B,A] = hpf12(wc, q);
            elseif( strcmp(this.type, 'bandpass'))
                [B,A] = bpf12(wc, q);
            else
                [B,A] = lpf12(wc, q);
            end;
            
            y = fastFilter(B,A,x);
            
            this.output.write(y);
        end
        
    end
end

function [B,A] = hpf12(wc, q)

    wc_lp = 1./(2*pi*wc);

    [B_lp, A_lp] = lpf12(wc_lp, q);

    b0 = B_lp(:,1);
    b1 = -B_lp(:,2);
    b2 = B_lp(:,3);

    a0 = A_lp(:,1);
    a1 = -A_lp(:,2);
    a2 = A_lp(:,3);

    B = [b0 b1 b2];
    A = [a0 a1 a2];
end

function [B,A] = lpf12(wc, q)

    wc = 2*pi*wc;

    a0 = 1 + 4*q./wc + 4./wc.^2;
    a1 = (2 - 8./wc.^2);
    a2 = (1 - 4*q./wc + 4./wc.^2);

    b0 = 1;
    b1 = 2;
    b2 = 1;

    A = [a0 a1 a2];
    B = [b0 b1 b2];
end

function [B,A] = bpf12(wc, q)

    b0 = q;
    b1 = zeros(size(q));
    b2 = -q;
    
    a0 = 1 + q + wc.^2;
    a1 = 2*wc - 2;
    a2 = 1 - q + wc.^2;
    
    B = [b0 b1 b2];
    A = [a0 a1 a2];
end