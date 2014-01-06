classdef Sum < Module
    
    properties(SetAccess=private)    
        output
        numberOfInputs
    end
        
    methods
       
        function this = Sum(name, numberOfInputs)
           
            this = this@Module(name);
            
            for n = 1:numberOfInputs
                
                this.createInputPort();
                
            end;
           
            this.numberOfInputs = numberOfInputs;
            this.output = this.createOutputPort();
        end
        
        function doUpdate(this,N)
           
            y = 0;
            
            for n = 1:this.numberOfInputs
                
                y = y + this.inputPorts(n).read(N);
                
            end;
            
            this.output.write( y );
        end
    end
end