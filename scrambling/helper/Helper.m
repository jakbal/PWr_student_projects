classdef Helper
    %HELPER klasa zawiraj¹ce niektóre metody pomocnicze
    
    methods (Static)
        function ber = calculateBER(originalSignal, outputSignal)
            errors = max(originalSignal.getSize(), outputSignal.getSize()) - min(originalSignal.getSize(), outputSignal.getSize());
            %pocz¹tkowo errors ma wartoœæ ró¿nicy miêdzy sygna³ami, po zaimplementowaniu kana³u z duplikacjami, ta wartoœæ bêdzie ró¿na od zera
            totalBits = max(originalSignal.getSize(), outputSignal.getSize()); %0 < ber < 1.00, dlatego totalbits to d³ugoœæ wiêkszego z sygna³ów
            
            for i = 1 : min(originalSignal.getSize(), outputSignal.getSize())
                if(originalSignal.getBitAt(i) ~= outputSignal.getBitAt(i)) %jeœli bity s¹ ró¿ne
                    errors = errors + 1;
                end
            end
            
            ber = errors/totalBits;
        end
        
        function o = insertToAlign64(signal)
            currentSize = signal.getSize();
            newSize = 64 * (floor((currentSize-1)/64) + 1);
            o = Signal(newSize);
            
            for i = 1 : currentSize
                o.setBitAt(i, signal.getBitAt(i));
            end
        end
    end
end