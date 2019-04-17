classdef DecoderEthernet < handle
    
    properties (Access = private)
        errorFlag,
        preamblesToCheck = 2, % liczba preambu³ do sprawdzenia, zarówno po lewej, jak i po prawej stronie
        preambleCheckScope = 2
    end
    
    methods (Access = private)
        function bestPreambleScore = checkForPreambleInScope(this, signal, i)
           bestPreambleScore = -1; % negatywny wynik jeœli preambu³a nie zosta³a znaleziona
          
           leftScope = i - this.preambleCheckScope;
           rightScope = this.preambleCheckScope*2 + leftScope;
           if leftScope < 1
              leftScope = 1;
           end
           
           while leftScope < signal.getSize() && leftScope <= rightScope
               if signal.getBitAt(leftScope) == 0 && signal.getBitAt(leftScope + 1) == 1
                    
                   foundPreambleScore = this.preambleCheckScope - abs(i - leftScope);   % oparty na dystansie
                   if foundPreambleScore > bestPreambleScore 
                      bestPreambleScore = foundPreambleScore; 
                   end
                   
               end
               leftScope = leftScope + 1;
           end
        end
        
        function dataIndex = resynchronization(this, signal, badFrameIndex)
            % wyniki dla preambu³y wynosz¹ 0, i nie zosta³y jeszcze znalezione, wiêc indekx = -1
            potentialPreamblesScores = zeros(1,2*this.preamblesToCheck);
            potentialPreamblesIndexes = zeros(1,2*this.preamblesToCheck);
            
            for i = 1 : 2*this.preamblesToCheck
                potentialPreamblesIndexes(i) = -1;
            end
            
            % idz w lewo
            iterator = badFrameIndex - 1;
            foundPreamblesLeft = 0;
            
            while iterator >= 1 && foundPreamblesLeft ~= this.preamblesToCheck
                while iterator >= 1 && ~(signal.getBitAt(iterator) == 0 && signal.getBitAt(iterator+1) == 1)
                    iterator = iterator - 1;
                end
                
                if iterator >= 1
                    % found '01' preamble
                    foundPreamblesLeft = foundPreamblesLeft + 1;
                    potentialPreamblesIndexes(foundPreamblesLeft) = iterator;
                    
                    % score logic
                    score = 0;
                    % wynik na lewo
                    currentPreambleIndex = iterator - 66;
                    while currentPreambleIndex >= 1
                       score = score + this.checkForPreambleInScope(signal, currentPreambleIndex);
                       currentPreambleIndex = currentPreambleIndex - 66;
                    end
                    % wynik na prawo
                    currentPreambleIndex = iterator + 66;
                    while currentPreambleIndex < signal.getSize()
                       score = score + this.checkForPreambleInScope(signal, currentPreambleIndex);
                       currentPreambleIndex = currentPreambleIndex + 66;
                    end
                    
                    % zapisanie wyniku
                    potentialPreamblesScores(foundPreamblesLeft) = score;
                    
                    iterator = iterator - 1;
                end
            end
            
            % idz w prawo
            iterator = badFrameIndex + 1;
            foundPreamblesRight = 0;
            
            while iterator < signal.getSize() && foundPreamblesRight ~= this.preamblesToCheck
                while iterator < signal.getSize() && ~(signal.getBitAt(iterator) == 0 && signal.getBitAt(iterator+1) == 1) 
                    iterator = iterator + 1;
                end
                
                if iterator < signal.getSize()
                    % found '01' preamble
                    foundPreamblesRight = foundPreamblesRight + 1;
                    potentialPreamblesIndexes(foundPreamblesRight + foundPreamblesLeft) = iterator;
                    
                     % score logic
                    score = 0;
                    % wynik na lewo
                    currentPreambleIndex = iterator - 66;
                    while currentPreambleIndex >= 1
                       score = score + this.checkForPreambleInScope(signal, currentPreambleIndex);
                       currentPreambleIndex = currentPreambleIndex - 66;
                    end
                    % wynik na prawo
                    currentPreambleIndex = iterator + 66;
                    while currentPreambleIndex <= signal.getSize()
                       score = score + this.checkForPreambleInScope(signal, currentPreambleIndex);
                       currentPreambleIndex = currentPreambleIndex + 66;
                    end
                    
                    % zapisanie wyniku
                    potentialPreamblesScores(foundPreamblesRight + foundPreamblesLeft) = score;
                    
                    iterator = iterator + 1;
                end
            end
            
            % znalezienie najlepszego dopasowania
            bestMatchScore = -55555;
            bestMatchIndex = -1;
            for i = 1 : 2*this.preamblesToCheck
                if potentialPreamblesScores(i) > bestMatchScore
                    bestMatchScore = potentialPreamblesScores(i);
                    bestMatchIndex = i;
                end
            end
            
            dataIndex = potentialPreamblesIndexes(bestMatchIndex) + 2;
            
        end
    end
    
    methods
        function decodedSignal = decode(this, signal)
            % czyszczenie poprzednich flag z b³êdami
            this.errorFlag = false;
            
            signalSize = signal.getSize();
            numberOfFrames = floor(signalSize/66);
            decodedSignal = Signal(numberOfFrames*64);
            
            k = 1; % przechowuje decodedSignal indeks iteratora
            i = 1;
            while i < signalSize
                % sprawdzenie dla preambu³y
                if signal.getBitAt(i) ~= 0 || signal.getBitAt(i+1) ~= 1
                    this.errorFlag = true;
                    i = this.resynchronization(signal, i);
                else
                    i = i + 2;
                end
                    
                limit = i + 64;
                %kopiowanie wszystkich bitów ramki o d³ugoœci 64 bitów
                while  i <= signalSize && i < limit
                    decodedSignal.setBitAt(k, signal.getBitAt(i));
                    k = k + 1;
                    i = i + 1;
                end
            end
        end
        
        function o = wasGood(this)
            o = not(this.errorFlag);
        end
        
    end
    
end
        