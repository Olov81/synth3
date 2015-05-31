classdef OutputPort < handle

    properties (Access = private)    
        owner
    end
    
    properties (SetAccess = private)
        
        data
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
            
            dim = size(this.data);
            
            datalen = dim(1);
            
            if( datalen < N )
                y = [this.data; this.data(datalen)*ones(N-datalen,dim(2))];
            else
                y = this.data(1:N,:);
            end;
            
        end;
        
        function resetUpdateStatus(this)
        
            this.owner.resetUpdateStatus();
            
        end;
        
    end
end