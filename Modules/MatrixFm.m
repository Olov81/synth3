classdef MatrixFm < Module
   
    properties(SetAccess = private)
        
        frequencyInput
        output
        gateInput
    end
    
    properties(Access = private)
    
        Ts
        numberOfOperators
        envOutputs
    end
    
    properties
       
        matrix
        envelopes
        ratios
    end
    
    methods
       
        function this = MatrixFm(name, fs, numberOfOperators)
           
            this = this@Module(name);
            this.Ts = 1/fs;
            this.numberOfOperators = numberOfOperators;
            this.matrix = zeros(numberOfOperators + 1, numberOfOperators);
%             this.matrix(end,1) = 1;
            this.ratios = ones(1,numberOfOperators);
            
            this.gateInput = this.createInputPort();
            this.frequencyInput = this.createInputPort();
            this.output = this.createOutputPort();
            
            this.envelopes = cell(1, numberOfOperators);
            this.envOutputs = cell(1, numberOfOperators);
            for( n = 1:numberOfOperators )
                this.envelopes{n} = this.addSubModule(EnvelopeGenerator([name ' envelope ' num2str(n)], fs));
                this.envelopes{n}.gateInput.connect(this.gateInput);
                this.envOutputs{n} = this.addSubModule(WaveWriter([name ' envelope ' num2str(n) ' output']));
                this.envOutputs{n}.input.connect(this.envelopes{n}.output);
            end;
        end
        
        function doUpdate(this, N)
        
            CV = this.frequencyInput.read(N);
            f = 0;
            y = zeros(N,1);
            operator = zeros(N, this.numberOfOperators);
            M = this.matrix;
            env = zeros(N, this.numberOfOperators);
            for( n = 1:this.numberOfOperators)
                env(:,n) = this.envOutputs{n}.y;
            end;
            
            for( k = 2:N )
    
                f = f + CV(k);

                for( n = 1:this.numberOfOperators )

                    x = 0;

                    for( m = 1:this.numberOfOperators )

                        x = x + M(m,n)*operator(k-1,m);

                    end;

                    operator(k,n) = (1/CV(k))*env(k,n)*sin(this.ratios(n)*2*pi*f*this.Ts + x);

                    y(k) = y(k) + this.matrix(this.numberOfOperators+1,n)*operator(k,n);

                end;

            end;
            
            this.output.write( y );
            
        end
        
    end
end