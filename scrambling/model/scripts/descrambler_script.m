clear;
%wywolanie skryptu scramblingu w celu weryfikacji wektora
%otrzymanego po descramblingu
fprintf("SCRAMBLING\n");
scrambler_script;
temp_frame = frame; 

%proced descramblingu w przypadku DVB przebiega tak samo, 
%jak proces scramblingu
for i=1 : length(signal)
    x = xor(temp_frame(1),xor(temp_frame(40),temp_frame(59)));
    temp_frame(2:end) = temp_frame(1:(end-1));
    temp_frame(1) = x;
    signal(i)= xor(signal(i),x);
end

fprintf("DESCRAMBLING:\n");
fprintf("Signal:    [");

for i=1 : length(signal)
    fprintf("%d ", signal(i));
end
fprintf("\b]\n");
