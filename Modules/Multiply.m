classdef Multiply < Module
   
    properties(SetAccess = private)
       
        output
        numberOfInputs
    end
    
    methods
        
        function this = Multiply(name, numberOfInputs)
           
            this = this@Module(name);
            this.numberOfInputs = numberOfInputs;
            
            for( n = 1:numberOfInputs )
                
                this.createInputPort();
                
                this.inputPorts(n).set( 1 );
                
            end;
            
            this.output = this.createOutputPort();
            
        end
        
        function doUpdate(this, N)
        
            y = 1;
            
            for( n = 1:this.numberOfInputs )
                
                y = y.*this.inputPorts(n).read(N);
                
            end
            
            this.output.write( y );
            
        end;
        
    end
end