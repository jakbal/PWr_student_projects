clear;

signal = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];
frame  = [0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1];
temp_frame = frame;

fprintf('Signal:    [');
for i = 1 : length(signal)
    fprintf('%d ', signal(i));
end
fprintf('\b]\n');

for i = 1 : length(signal)
    x = xor(temp_frame(1), xor(temp_frame(40), temp_frame(59)));    %xor bitu 1, 40, 59
    temp_frame(2:end) = temp_frame(1:(end-1));                      %przesuniêcie ramki o jeden
    temp_frame(1) = x;                                              %na pierwsz¹ pozycjê ramki wprowadzamy wynik xor
    signal(i) = xor(signal(i), x);                                  %xor bitu wejœcia(sygna³u) i wartoœci pseudolosowej(otrzymanej z ramki)       
end

fprintf('Scrambled: [');
for i = 1 : length(signal)
    fprintf('%d ', signal(i));
end
fprintf('\b]\n');
