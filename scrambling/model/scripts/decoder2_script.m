clc;

esignal=randi([0,1],1,127); %generuje 127-bitowy sygna³ w zakresie od 0 do 1. Normalnie bêdzie tu wchodzi³ ca³y wygenerowany sygna³

disp(esignal); % wyswietlenie sygnalu przed kodowaniem
newesignal=[]; %bedzie zbierala 64 bitowe ramki

while(~isempty(esignal))
    if(length(esignal)<64)
        esignal=esignal(3:length(esignal));%odciêcie pocz¹tkowych 2 bitów ostatniej ramki
        newesignal=horzcat(newesignal,esignal(1:length(esignal))); %do³¹czenie ostatniej ramki
        break;
    end
    esignal=esignal(3:length(esignal));%odciêcie pocz¹tkowych 2 bitów
    newesignal=horzcat(newesignal,esignal(1:64));
    esignal=esignal(65:length(esignal)); %odciêcie pocz¹tkowych 64 bitów
end
disp(newesignal); % sprawdzenie po kodowaniu