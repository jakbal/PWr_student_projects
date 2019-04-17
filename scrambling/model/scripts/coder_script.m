clc;

esignal=randi([0,1],1,127); %generuje 127-bitowy sygna³ w zakresie od 0 do 1. Normalnie bêdzie tu wchodzi³ ca³y wygenerowany sygna³
preambule = [0 1];

disp(esignal); % wyswietlenie sygnalu przed kodowaniem
temp=1;
org_signal_size = length(esignal);
newesignal=[]; %bedzie zbierala 66 bitowymi ramkami preambu³e+sygna³ wejsciowy

while(temp<org_signal_size)
    if(temp+64>org_signal_size)
        newesignal=horzcat(newesignal,horzcat(preambule,esignal(temp:org_signal_size)));
        break;
    end
    newesignal=horzcat(newesignal,horzcat(preambule,esignal(temp:temp+63))); 
    temp = temp + 64;
    if(temp+64>org_signal_size)
        newesignal=horzcat(newesignal,horzcat(preambule,esignal(temp:org_signal_size)));
        break;
    end
end
disp(newesignal); % sprawdzenie po kodowaniu