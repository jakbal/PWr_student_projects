classdef Descrambler < handle

    properties (Access = private)
        deafultLSFR
        tempLSFR
    end
    
    methods 
        function this = Descrambler(seed)
            if(nargin == 0)
                %domyslna ramka musi by ta sama co w Scrambler.m
                this.deafultLSFR = [0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1];
                this.tempLSFR = this.deafultLSFR;
            else
                this.deafultLSFR = seed;
                this.tempLSFR = this.deafultLSFR;
            end
        end
           
        function resetLSFR(this)
            this.tempLSFR = this.deafultLSFR;
        end
        
        function s = descrambleSignal(this, signal)
            for i=1 : signal.getSize()
               x = xor(this.tempLSFR(1),xor(this.tempLSFR(21),this.tempLSFR(37)));
               x = xor(x,signal.getBitAt(i));
              
               this.tempLSFR(2:end) = this.tempLSFR(1:(end-1)); %przesuniêcie ramki
               this.tempLSFR(1) = signal.getBitAt(i);           %wprowadzenie bitu sygna³u na pozycje pierwsz¹
               
               signal.setBitAt(i,x);
            end
            %zwroc sygnal         
            s = signal;
        end
        
        function printLSFR(this)   %wydruk stanu rejestru tempLSFR
            fprintf('LSFR :\n[');
            for i = 1 : size(this.tempLSFR,2)
                fprintf('%d, ', this.tempLSFR(i));
            end
            fprintf(' ]\n');
        end
        
    end
    
end

