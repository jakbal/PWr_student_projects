classdef Decoder2 < handle

    properties
        preamble = [0,1];
    end
    
    methods
        
        function this=Decoder2()
        end
        
        function decodedSignal = decode(this,signal)
            decodedSignal = signal; %funkcja musi miec co zwrocic
            
            if class(signal) == "Signal"
                %w petli co 64 bity usuwamy preambule
                p = floor( signal.getSize() / 66);  %ilosc potencjalnych preambul
                temp_preamble = [0,0];              %odczytana preambula na pozycji xx
                i = 1;
                
                while(i<=signal.getSize())
                    temp_preamble(1) = signal.getBitAt(i);
                    temp_preamble(2) = signal.getBitAt(i+1);
                    if(this.preamble == temp_preamble)
                        %jezeli preambula jest ok
                        %to po prostu j¹ usuñ                     
                        signal.removeBitAt(i);
                        signal.removeBitAt(i);
                        i = i + 64;
                    else      
                        %PODEJSCIE NOWE - doœæ naiwne, ale jakiekolwiek:
                        %usuwamy bity dopóki nie odnajdziemy takiej
                        %sytaucji, ¿e na miejscu i, i+1 wystêpuje poprawna
                        %preabu³a oraz wystêpuje ona 64 bity dalej na
                        %miejscach i+64, i+65
                        %dla sygna³u o jednostanym rozk³adzie jedynek i zer
                        %prawdobodobieñstwo takiej sytaucji wynosi 
                        %1/4 * 1/4 = 1/16
                        %zatem je¿eli j¹ napotkamy to s¹ to znaczne szanse,
                        %¿e mechanizm resynchronizacji trafi³ na w³aœciwe
                        %bity preambu³
                        
                        still = true;           %odpowiada za iteracjê pêtli while która resynchronizuje sygna³                       
                        signal.removeBitAt(i);  %wpierw nale¿y usun¹æ poprzedni¹ b³êdn¹ preambu³ê
                        signal.removeBitAt(i);
                                                %dalej pozostajemy na
                                                %pozycji i gdzie powinna
                                                %byæ preambu³a
                        while(still)
                            if(this.preamble(1) == signal.getBitAt(i) && this.preamble(2) == signal.getBitAt(i+1) && this.preamble(1) == signal.getBitAt(i+66) && this.preamble(2) == signal.getBitAt(i+67) )
                                signal.removeBitAt(i);
                                signal.removeBitAt(i);
                                %poniewa¿ trafiliœmy na sytuacjê
                                %sprzyjaj¹c¹, to przerywamy proces
                                %resynchronizacji 
                                %oraz przesuwamy siê 64 bity dalej
                                %tak jak ma to miejsce w prawid³owym
                                %uk³adzie bitów preambu³y
                                still = false;
                                i = i + 64;
                            else
                                %je¿eli nie jest to sytuacja sprzyjaj¹ca
                                %jak w warunku if(...),
                                %to usuwamy nastêpne dwa przetoworzone bity,
                                %które mog³y stanowiæ prawid³ow¹ preambu³ê
                                signal.removeBitAt(i);
                                signal.removeBitAt(i);
                                %poniewa¿ istnia³a mo¿liwoœæ ¿e gdy i by³o
                                %ju¿ ostatni¹ lini¹ bitów, to algorytm
                                %nigdy nie móg³ przecie¿ znaleŸæ kolejnych
                                %64 bitów, bo ich nie by³o
                                %a sam program wpada³ w pêtlê nieskoñczon¹
                                %poni¿szy if(...) sprawdza czy po usuwaniu
                                %elementów przypadkiem i nie przekroczy³
                                %ju¿ zakresu, który jest sens sprawdzaæ
                                if(i>signal.getSize())
                                    still = false;
                                end
                                %i dalej kontynuujemy szukanie sprzyjaj¹cej
                                %nam sytaucji 01(64 bity dalej...)01...
                            end
                        end
                        
                    end
                    
                    %p = p - 1;
                    
                end
            else
                return
            end
            
            decodedSignal = signal; %odkodowany i zresynchronizowany sygna³
            
        end 
       
    end
    
end
