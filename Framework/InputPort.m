classdef InputPort < handle
   
    properties (SetAccess = private)
    
        connection
        
    end
    
    properties(Access=private)
        
        constant
        
    end
    
    methods
       
        function this = InputPort(initialValue)
            
            v = 0;
            
            if( nargin > 0 )
                v = initialValue;
            end;
            
            this.constant = Constant( 'Constant', v );
            
            this.connection = this.constant.output;
            
        end;
        
        function update(this, N)
        
            this.connection.update(N);
            
        end;
        
        function connect(this, outputPort)
            
            this.connection = outputPort;
            
        end;
        
        function set(this, value)
        
            this.constant.value = value;
            this.connection = this.constant.output;
                
        end;
        
        function [y, numberOfChannels] = read(this, N)
            
            y = this.connection.read( N );
            
            dim = size(y);

            numberOfChannels = dim(2);
            
        end;
        
        function resetUpdateStatus(this)
        
            this.connection.resetUpdateStatus();
            
        end;
        
    end
end