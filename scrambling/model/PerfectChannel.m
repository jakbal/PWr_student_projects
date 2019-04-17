classdef PerfectChannel < Channel
    %ten kana� nie b�dzie generowa� przek�ama� w sygnale
    methods
        function this = PerfectChannel()
            this.signal = [];                   %dziedziczone z klasy abstrakcyjnej Channel
        end
        
        function sendSig(this, signal)
            if class(signal) == "Signal"        %tylko je�li wysy�any obiekt jest instancj� Signal
                this.signal = signal.copy;      %wysy�amy kopi� sygna�u
            else
                return
            end
        end
        
        function received = receiveSig(this)
            if(isempty(this.signal))
                received = Signal(0);
            else
                received = this.signal;
                this.signal = [];
            end
        end
    end
end