classdef SamplePlayer < Module
    
    properties (SetAccess = private)
        gateInput
        output
        ampEnvelope
    end
    
    properties
        sample
    end
    
    methods
        
        function this = SamplePlayer(name, fs)
            
            this = this@Module(name);
           
            this.ampEnvelope = EnvelopeGenerator('Amp envelope', fs);
            this.gateInput = this.createInputPort();
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this, N)
            
            gate = this.gateInput.read(N);
            
            edges = detectPositiveEdges(gate, 1e-3);
           
            dim = size(this.sample);
          
            this.ampEnvelope.gateInput.set(1);
            this.ampEnvelope.update(dim(1));
            ampEnv = this.ampEnvelope.output.read(dim(1));
            
            y = 0;
            if( dim(2) == 1 )
                y = fconv(edges, ampEnv.*this.sample);
            elseif( dim(2) == 2 )
                yL = fconv(edges, ampEnv.*this.sample(:,1));
                yR = fconv(edges, ampEnv.*this.sample(:,2));
                y = [yL yR];
            end;
            
            this.output.write(y);
        end;
            
	end 
end

function y = detectPositiveEdges(gate, threshold)

    edges = find(diff([0; gate]) > threshold);

    y = zeros(size(gate));

    y(edges) = gate(edges+1);

end