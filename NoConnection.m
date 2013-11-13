classdef NoConnection
    
    methods
        
        function update(~, ~)
        end;
        
        function y = read(~, N)
            
            y = zeros(N,1);
            
        end;
        
    end

end