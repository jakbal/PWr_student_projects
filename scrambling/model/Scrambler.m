classdef Scrambler < handle
    
    properties (Access = private)
        defaultLSFR
        tempLSFR
    end
    
    methods
        function this = Scrambler(seed) %konstruktor
            if(nargin == 0)             %number of function input arguments = 0 -> konstruktor bezparametryczny
                this.defaultLSFR = [0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1];
                this.tempLSFR = this.defaultLSFR;
            else                        %seed z parametru
                this.defaultLSFR = seed;
                this.tempLSFR = seed;
            end
        end
        
        function resetLSFR(this)    %reset rejestru do stanu pocz¹tkowego
            this.tempLSFR = this.defaultLSFR;
        end
        
        function scr = scrambleSignal(this, signal)                                   %funkcja scrambluj¹ca
            for i = 1:signal.getSize()  
                x = xor(this.tempLSFR(1), xor(this.tempLSFR(21), this.tempLSFR(37))); %xor 1,21 i 37 indeksu lfsr
                x = xor(signal.getBitAt(i), x);                                       %xor danego bitu sygna³u oraz wartoœci z poprzedniego xora
                signal.setBitAt(i, x);                                                %ustawienie bitu sygna³u wyjœciowego
                
                this.tempLSFR = [signal.getBitAt(i), this.tempLSFR(1:end-1)];         %przesuniêcie rejestru
            end
            %zwroc sygnal
            scr = signal;        
            %this.resetLSFR;
            %podczas przesy³u ramka nie bêdzie musia³a byæ resetowana, bo w
            %scramblerze i descramblerze bêd¹ mia³y identyczn¹ zawartoœæ
            %i bêd¹ przesuwaæ siê zawsze o tyle samo
        end
        
        function printLSFR(this)       %wydruk stanu rejestru tempLSFR
            fprintf('LSFR:\n[');
            for i = 1 : size(this.tempLSFR,2)
                fprintf('%d, ', this.tempLSFR(i));
            end
            fprintf(' ]\n');
        end
        
    end
end