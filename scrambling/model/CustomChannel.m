 classdef CustomChannel < Channel
    %CUSTOMCHANNEL Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Access = private)
        probability; %dla funkcjonalnosci bsc
        desynchNumOfBits; %ilosc bitow po ktorych sie desynchronizuje
        periodNumOfBits; %okresowe przeklamanie bitu
    end
    
    methods (Access = public)
        
        function this = CustomChannel(prob, desynch, period)
            
            if(prob<=1 && prob>=0)
                this.probability = prob;
            else
                this.probability = 0;
            end
            
            if(desynch>1)
                this.desynchNumOfBits = desynch;
            else
                this.desynchNumOfBits = 21; %tu nale¿y przyj¹æ jedn¹ wartoœæ, która bêdzie domyslna, a najlepiej niech pochodzi z jakiejœæ normy ITU, czy ISO
            end
            
            if(period>0)
                this.periodNumOfBits = period;
            else
                this.periodNumOfBits = 0;
            end
            
        end
        
        function sendSig(this, signal)
            if (class(signal) == "Signal")      %tylko jeœli wysy³any obiekt jest instancj¹ Signal
                this.signal = signal.copy;      %wysy³amy kopiê sygna³u do kana³u
                this.passThroughCC();             %przepuszczenie kopii sygna³u przez CC
            else
                return
            end
        end
       
        function received = receiveSig(this)
            if(~isempty(this.signal))    %je¿eli signal jest, to go wyœlij
                received = this.signal;
            else                        % je¿eli go nie ma to wyslij pusty wektor
                received = [];
            end
            this.signal = [];
        end 
        
    end
    
    methods (Access = private)
        
        function passThroughCC(this)
            this.BSC();
            this.periodicDistortion();
            this.desynchronization();
        end
        
        function BSC(this)
            if(this.probability ~= 0)
                temp_sig = zeros(1,this.signal.getSize()); %alokacja wektora o d³ugoœci sygna³u
                for i=1 : this.signal.getSize()
                    temp_sig(i) = this.signal.getBitAt(i);
                end
                temp_sig = bsc(temp_sig, this.probability);
                for i=1 : this.signal.getSize()
                    this.signal.setBitAt(i, temp_sig(i));
                end
            end
        end
        
        function periodicDistortion(this)
            if(this.periodNumOfBits ~= 0)
                k = floor(this.signal.getSize()/this.periodNumOfBits);
                i = this.periodNumOfBits;
                while(k>0)
                    this.signal.negBitAt(i);
                    i = i + this.periodNumOfBits;
                    k = k - 1;
                end
            end
        end
        
        function desynchronization(this)
            counter = 0;
            currentDesynchBit = this.signal.getBitAt(1);
            i=1;
            while(i <= this.signal.getSize())
                
                if(this.signal.getBitAt(i) == currentDesynchBit)
                    counter = counter + 1;
                else
                    currentDesynchBit = this.signal.getBitAt(i);
                    counter = 1;
                end
                
                %je¿eli pojawi siê k-te wyst¹pienie bitu to
                %desynchronizacja, gdzie k wyznacza defacto desynchNumOfBits
                if(counter >= this.desynchNumOfBits)
                    %desynchronizacja bêdzie polegaæ na pseudoloswym
                    %wstawieniu lub usuniêciu aktualnie przetwarzanego 
                    %bitu, który siê powtórzy³
                    if(rand()>0.5)
                        %usuniêcie bitu
                        this.signal.removeBitAt(i);
                        %iterator i wskazuje na przesuniêtu o jeden w lewo
                        %bit, zatem nie trzeba modyfikowaæ i
                    else
                        %wstawienie bitu powtarzaj¹cego siê na pozycjê
                        %za indeksem i
                        this.signal.insertBitAt(i, currentDesynchBit);
                        %i wskazuje na bit przed nowym bitem zatem nale¿y
                        %przesun¹æ i za nowo wstawiony bit
                        %inaczej na kolejny bit oryginalnego sygna³u
                        i = i + 2;
                    end
                else
                    %je¿eli desynchNumOfBits nie zosta³a przekroczona
                    %to po prostu przechodzimy z i do nastepnego znaku
                    i = i + 1;
                end
                
            end
        end
        
    end
    
end

