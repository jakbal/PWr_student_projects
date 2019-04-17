classdef SignalGenerator < handle
    %generator sekwencji x * 64b
    %x to d³ugoœæ ramki podawana przez u¿ytkownika
    
    properties
        numOfFrames    %user defined values: number of frames 
        p              %probability
    end
    
    methods (Access  = public)
        function obj = SignalGenerator(num, prob)
            if((prob>=0 && prob<=1) && num >=0)
                obj.p = prob;
                obj.numOfFrames = num;
            else
                obj.p = 0;
                obj.numOfFrames = (-1) * num;
            end
        end
        
        function setProbability(obj, prob)
            if(prob>=0 && prob<=1)
                obj.p = prob;
            else
                obj.p = 0;
            end
        end
        
        function setFramesNumber(obj, num)
            if(num >= 0)
                obj.numOfFrames = num;
            else
                obj.numOfFrames = (-1) * num;
            end
        end
        
        function gen = generateSignal(obj)
            gen = Signal(obj.numOfFrames * 64); %d³ugoœæ sygna³u to iloœæ ramek razy iloœæ bitów (64b)
            
            for i = 1: gen.getSize()
                if( (0.5 + obj.p/2) >= rand)     %szansa ¿e z prawdopodobieñstwiem p wstawi siê jedynka
                    gen.setBitTrue(i);           %je¿eli p = 0 to musi byæ 0.5>=rand poniewa¿ rozk³ad 1/0 musi byæ fifty-fifty                                               
                end                              %wymaga to wprowadzonego warunku, na jego podstawie bêdzie zwiêkszaæ siê
            end                                  %liczba jedynek zawartych w sygnale
            
        end
    end
    
end

