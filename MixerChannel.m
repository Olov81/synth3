classdef MixerChannel < Module

    properties
        
    end
    
    properties(SetAccess = private)
        
        levelInput
        lowShelfEq
        highShelfEq
        paramEq1
        paramEq2
        sendLevelInput
        input
        output
        sendOutput
        
    end
    
    properties(Access = private)
        
        levelGain
        sendGain
    end
    
    methods
        
        function this = MixerChannel(name)
            
            this = this@Module(name);
            
            this.input = this.createInputPort();
            this.levelInput = this.createInputPort(1.0);
            this.sendLevelInput = this.createInputPort();
            
            this.lowShelfEq = this.addSubModule(ShelfEq([name ' Low Shelf'],'low'));
            this.highShelfEq = this.addSubModule(ShelfEq([name ' High Shelf'], 'high'));
            this.paramEq1 = this.addSubModule(ParametricEq([name ' Param EQ 1']));
            this.paramEq2 = this.addSubModule(ParametricEq([name ' Param EQ 2']));
            
            this.levelGain = this.addSubModule(Gain([name ' Level'], 1.0));
            this.sendGain = this.addSubModule(Gain([name ' Send Level'], 0.0));

            this.lowShelfEq.input.connect(this.input);
            this.highShelfEq.input.connect(this.lowShelfEq.output);
            this.paramEq1.input.connect(this.highShelfEq.output);
            this.paramEq2.input.connect(this.paramEq1.output);
            
            this.levelGain.input.connect(this.paramEq2.output);
            this.levelGain.gainInput.connect(this.levelInput);
            
            this.sendGain.input.connect(this.highShelfEq.output);
            this.sendGain.gainInput.connect(this.sendLevelInput);
            
            this.output = this.levelGain.output;
            this.sendOutput = this.sendGain.output;
            
            this.levelInput.set( 1.0 );
            
            this.lowShelfEq.bypass = true;
            this.highShelfEq.bypass = true;
            this.paramEq1.bypass = true;
            this.paramEq2.bypass = true;
            
        end;
        
        function doUpdate(this, N)
            
        end;
        
    end
end