classdef StereoOutputPort < handle

    properties (Access = private)
    
        data
        owner
    end
    
    methods
        
        function this = StereoOutputPort(owner)
            
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
                y = [this.data; this.data(datalen)*ones(N-datalen,2)];
            else
                y = this.data(1:N,:);
            end;
            
        end;
        
        function resetUpdateStatus(this)
        
            this.owner.resetUpdateStatus();
            
        end;
        
    end
end