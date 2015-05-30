classdef Mixer < Module
   
    properties
        mainOutput
        sendOutput
        returnInput
        channels
        outputLevelInput
    end
    
    properties(Access=private)
        mainSum
        sendSum
        outputSum
        outputGain
    end
    
    methods
        
        function this = Mixer(name, numberOfInputs)
    
            this = this@Module(name);
            this.mainSum = this.addSubModule(Sum('Main sum', numberOfInputs));
            this.sendSum = this.addSubModule(Sum('Send sum', numberOfInputs));
            this.outputSum = this.addSubModule(Sum('Output sum', 2));
            this.outputGain = this.addSubModule(Gain('Output gain',1));
            
            this.channels = MixerChannel.empty;
            
            for n = 1:numberOfInputs
                channel = this.addSubModule(MixerChannel([name ' Channel ' num2str(n)]));
                this.channels(n) = channel;
                this.mainSum.inputPorts(n).connect(channel.output);
                this.sendSum.inputPorts(n).connect(channel.sendOutput);
            end;
            
            this.returnInput = this.createInputPort();
            this.outputLevelInput = this.outputGain.gainInput;
            
            this.outputSum.inputPorts(1).connect(this.mainSum.output);
            this.outputSum.inputPorts(2).connect(this.returnInput);
            this.outputGain.input.connect(this.outputSum.output);

            this.sendOutput = this.sendSum.output;
            this.mainOutput = this.outputGain.output;
        end;
        
        function doUpdate(this, N)
            

            
        end;
        
    end
end