classdef OutputPort < handle

    properties (Access = private)
    
        data
        owner
    end
    
    methods
        
        function this = OutputPort(owner)
            
            this.data = 0;
            this.owner = owner;
            
        end;
        
        function update(this, N)
        
            this.owner.update( N );
            
        end;
        
        function write(this, data)
            
            this.data = data;
            
        end;
        
        function y = read(this, N)
            
            datalen = length(this.data);
            
            if( datalen < N )
                y = [this.data; 0*ones(N-datalen,1)];
            else
                y = this.data(1:N);
            end;
            
        end;
    end
end