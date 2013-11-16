classdef Module < handle & matlab.mixin.Heterogeneous
   
    properties
        name
    end
    
    properties (SetAccess = private)
        inputPorts
        outputPorts
        subModules
        isUpdated
    end
    
    methods (Abstract)
        
        doUpdate(this, N)
        
    end
    
    methods
        
        function this = Module(name)
        
            this.inputPorts = InputPort.empty;
            this.outputPorts = OutputPort.empty;
            this.subModules = EmptyModule.empty;
            this.isUpdated = false;
            this.name = name;
        end
        
        function resetUpdateStatus(this)
        
            for( n = 1:length(this.subModules) )
                
                this.subModules(n).resetUpdateStatus();
                
            end;
                
            this.isUpdated = false;
            
        end;
        
        function update(this, N)
            
            if( this.isUpdated == true )
                return;
            end;
            
            for( n = 1:length( this.inputPorts ) )
                
                this.inputPorts(n).update(N);
                
            end;
            
            for( n = 1:length(this.subModules) )
                
                this.subModules(n).update(N);
                
            end;
                
            this.doUpdate(N);
            
          
            this.isUpdated = true;
            
            disp([this.name ' updated'])
        end;
        
        function module = addSubModule(this, module)
            
            this.subModules(end+1) = module;
            
        end;
            
        function port = createInputPort(this, initialValue)

            if( nargin > 1 )
                port = InputPort( initialValue );
            else
                port = InputPort;
            end;
            
            this.inputPorts(end+1)= port;
            
        end;
        
        function port = createOutputPort(this)
            
            port = OutputPort(this);
            
            this.outputPorts(end+1) = port;
            
        end;
    end
end