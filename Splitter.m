classdef Splitter < Module
    
    properties(SetAccess=private)    
        input
        numberOfOutputs
    end
        
    methods
       
        function this = Splitter(name, numberOfOutputs)
           
            this = this@Module(name);
            
            for n = 1:numberOfOutputs
                
                this.createOutputPort();
                
            end;
           
            this.numberOfOutputs = numberOfOutputs;
            this.input = this.createInputPort();
        end
        
        function doUpdate(this,N)
            
            x = this.input.read(N);
            
            for n = 1:this.numberOfOutputs
                
                this.outputPorts(n).write(x);
                
            end;
        end
    end
end