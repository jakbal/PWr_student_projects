classdef BSChannel < Channel
          %BSC - binary symetric channel
    
    properties (Access = private)
        p %prawdopodobienstwo przek³amania
    end
    
    methods
        function obj = BSChannel(probability)
            if(nargin == 0)
                obj.p=0;
            else
                if(probability >= 0 & probability <=1)
                    obj.p = probability;
                else
                    obj.p = 0;
                end
            end
            obj.signal = [];
        end %koniec konstruktora
        
        function sendSig(obj, signal)
            if class(signal) == "Signal"        %tylko jeœli wysy³any obiekt jest instancj¹ Signal
                obj.signal = signal.copy;       %wysy³amy kopiê sygna³u do kana³u
                obj.passThroughBSC;             %przepuszczenie kopii sygna³u przez kana³ BSC
            else
                return
            end
        end
       
        function received = receiveSig(obj)
            if(~isempty(obj.signal))    %je¿eli signal jest, to go wyœlij
                received = obj.signal;
                obj.signal = [];
            else                        % je¿eli go nie ma to wyslij pusty wektor
                received = [];
                obj.signal = [];
            end
        end
        
    end
    
    methods (Access = private)
        function passThroughBSC(obj)
            %temp_sig bêdzie binarnym wektorem otrzymanego sygna³u 
            temp_sig = zeros(1,obj.signal.getSize()); %alokacja wektora o d³ugoœci sygna³u
            for i=1 : obj.signal.getSize()
                temp_sig(i) = obj.signal.getBitAt(i);
            end
            
            %wektor ten mo¿e byæ przepuszczony przez funkcjê bsc
            temp_sig = bsc(temp_sig,obj.p); %do funkcji bsc przekazujemy ustawione prawdopodobieñstwo - p
            
            %nastêpnie nale¿y ustawiæ bity przechowywanego sygna³u, je¿eli
            %w kanale zosta³y one zmienione
            for i=1 : obj.signal.getSize()
                obj.signal.setBitAt(i, temp_sig(i));
            end
        end
    end
    
end

