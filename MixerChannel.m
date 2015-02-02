classdef MixerChannel < Module

    properties
        
    end
    
    properties(SetAccess = private)
        
        levelInput
        lowShelfEq
        highShelfEq
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
            this.levelInput = this.createInputPort();
            this.sendLevelInput = this.createInputPort();
            
            this.lowShelfEq = this.addSubModule(ShelfEq([name ' Low Shelf'],'low'));
            this.highShelfEq = this.addSubModule(ShelfEq([name ' High Shelf'], 'high'));
            this.levelGain = this.addSubModule(Gain([name ' Level'], 1.0));
            this.sendGain = this.addSubModule(Gain([name ' Send Level'], 0.0));

            this.lowShelfEq.input.connect(this.input);
            this.highShelfEq.input.connect(this.lowShelfEq.output);
            
            this.levelGain.input.connect(this.highShelfEq.output);
            this.levelGain.gainInput.connect(this.levelInput);
            
            this.sendGain.input.connect(this.highShelfEq.output);
            this.sendGain.gainInput.connect(this.sendLevelInput);
            
            this.output = this.levelGain.output;
            this.sendOutput = this.sendGain.output;
            
        end;
        
        function doUpdate(this, N)
            
        end;
        
    end
end