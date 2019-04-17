classdef Signal < handle
    properties
        size
        bits
    end
    
    methods
        function this = Signal(parameter)   %konstruktor
            if (nargin ~= 0)    %jeœli nie zero
                this.bits = logical.empty;  %ustawiamy bity na puste
                if (isnumeric(parameter))   %jeœli parametr jest numeryczny
                    this.size = parameter;  %iloœc bitów 
                    for i = 1 : parameter
                        this.bits(i) = false;   %inicjalizacja fa³szem
                    end
                else
                    fromFile = importdata(parameter);  %jeœli parametr jest plikiem
                    this.size = fromFile(1);           %pierwszy wiersz zawiera rozmiar
                    for i = 1 : this.size
                        this.bits(i) = (fromFile(k+1) == 0).*false + (fromFile(k+1) ~= 0).*true;  %this.bits(i) = (from_file(k+1) == 0) ? false : true
                    end
                end
            else
                this.size = 0;              %jeœli brak parametru -> iloœæ bitów = 0;
            end   
        end
        
        %funkcje operuj¹ce bezpoœrednio na bitach
        
        function bit = getBitAt(this, i)    %getter bitu na pozycji i (zwraca jako wartoœæ liczbow¹)
            if (i >= 1 && i <=this.size)
                bit = this.bits(i).*1 + ~this.bits(i).*0; %bit = (this.bits(i)) ? 1 : 0;
            else
                %disp('getBitAt(' + i +') Index out of bound! Signal is ' + this.size + 'b!');
                %bit = [];
                %lepiej bêdzie zwróciæ wartoœæ sygnalizuj¹c¹ brak bitu na
                %danej pozycji, szczególnie dla mechanizmu resynchronizacji
                bit = -1;
            end
        end
        
        function setBitTrue(this, i)            %setter bitu na pozycji i (wartoœci¹ true)
            if (i >= 1 && i <=this.size)
                this.bits(i) = true;
            else
                disp("setBitTrue(" + i + ") Index out of bound! Signal is " + this.size + "b!");
            end
        end
        
        function setBitFalse(this, i)            %setter bitu na pozycji i (wartoœci¹ false)
            if (i >= 1 && i <=this.size)
                this.bits(i) = false;
            else
                disp("setBitFalse(" + i + ") Index out of bound! Signal is " + this.size + "b!");
            end
        end
        
        function setBitAt(this, i, value)         %setter bitu na pozycji i zadan¹ wartoœci¹
            if (value == 1)
                this.setBitTrue(i);
            else
                this.setBitFalse(i);
            end
        end
        
        function negBitAt(this, i)              %negacja bitu na pozycji i
            if (i >= 1 && i <=this.size)
                this.bits(i) = ~this.bits(i);
            else
                %disp('negBitAt(' + i + ') Index out of bound! Signal is ' + this.size + 'b!');
            end
        end
        
        function removeBitAt(this, i)           %usuniêcie bitu na pozycji i
            if(i >= 1 && i <=this.size)
                 prevBits = this.bits(1 : i-1);              %bity na mniejszych indeksach do bitu poprzedzaj¹cego i
                 nextBits = this.bits(i+1 : this.size);      %bity na wiêkszych indeksach do koñca sygna³u
           
                 this.bits = [prevBits nextBits];           %zestawienie nowego sygna³u bez i-tego bitu
                 this.size = this.size - 1;                   %dekrementacja iloœci bitów
            end
        end
        
        function insertBitAt(this, i, value) %wstawienie bitu o wartoœci value na pozycjê PO danym indeksie
            prevBits = this.bits(1 : i);            %jak w funkcji removeBitAt
            nextBits = this.bits(i+1 : this.size);
            
            this.bits = [prevBits logical(value) nextBits];   %zestawienie nowego sygna³u z konwersj¹ value na wartoœæ logiczn¹
            this.size = this.size + 1;                          %inkrementacja iloœci bitów
        end
        
        %funkcje pomocnicze
        
        function size = getSize(this)       %getter rozmiaru
            size = this.size;
        end     
        
        function value = decimalValue(this) %zwraca wartoœc decymaln¹ sygna³u
            value = 0;  %inicjalizacja zerem
            for i = 1 : this.size
                value = value + (2 ^ (i - 1)) * this.getBitAt(i);
            end
        end
        
        function cpy = copy(this)           %tworzy kopiê zadanego sygna³u
            cpy = Signal(this.size);        %cpy = new signal(this.size)
            for i = 1 : cpy.size
                cpy.bits(i) = this.bits(i); %przepisanie wartoœci
            end
        end
        
        function printSignal(this)          %wydruk sygna³u
            disp('Current Signal: ');
            fprintf('[\n');
            for i = 1 : this.size
               fprintf('%d ', this.bits(i));
               if(mod(i,64) == 0)
                   fprintf("\n");
               end
            end
            fprintf(']\n');
        end
        
        function signal = toString(this)    %konwersja sygna³u na string, u¿ywamy
            signal = string();
            for i = 1 : this.size
                if(this.bits(i))
                    signal = strcat(signal, '1');
                else
                    signal = strcat(signal, '0');
                end
            end                       
        end 
    end
    
end