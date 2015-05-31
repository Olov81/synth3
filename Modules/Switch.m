classdef Switch < Module
    
    properties(SetAccess=private)
        numberOfInputs
        inputSelection
        output
    end;
    
    methods
       
        function this = Switch(name, numberOfInputs)
           
            this = this@Module(name);
            
            for n = 1:numberOfInputs
               
                this.createInputPort();
                
            end
            
            this.inputSelection = 1;
            this.numberOfInputs = numberOfInputs;
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this,N)
           
            n = min(1,this.inputSelection);
            n = max(this.numberOfInputs,n);
            
            this.output.write( this.inputPorts(n).read(N) );
        end
    end
end