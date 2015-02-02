classdef PolySynth < EmptyModule
    
    properties(SetAccess=private)

    end
    
    properties(Access=private)
        
        vco1Gain
        vco2Gain

        vcf
        vca
        
        vcoSum
        cutoffSum
        
        pitchSum
    end
    
    methods
        
        function this = PolySynth(name,fs)
           
            this = this@EmptyModule(name);
            
        end
    end
end