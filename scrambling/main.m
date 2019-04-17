clear;
%dodanie œcie¿ek do folderów, klasy w nich widoczne s¹ osi¹galne
addpath(genpath('view'));
addpath(genpath('model'));
addpath(genpath('helper'));

%odpalenie gï¿½ï¿½wnego widoku aplikacji - czyli wywolanie funkcji
%zdefiniowanej w glownyWidok.m, ktï¿½ra z kolei odpala figure
%glownyWidok.fig, stworzonï¿½ przy pomocy GUIDE (lewym na glownyWidok.fig i
%edytuj w GUIDE)
FinalView();

%UWAGA: zakomentowa³em wyœwietlanie sygna³y, gdy¿ chcia³em skupiæ siê tylko
%na BER i rozmiarze sygna³y cop po procesie resynchronizacji

%LSFR musi miec d³ugoœæ conajmniej 39 bitów!!!
%LSFR = [0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1];
G = SignalGenerator(5, 0.5); %powtarzalnoœæ jedynek = 0.5
S = Scrambler();
D = Descrambler();
Enc = Encoder();
Dec = Decoder2();
CC = CustomChannel(0.01,0,0);%bsc = 0.01, desynch = 21, period=0
H = Helper();

%zakomnetowano procesy scramblingu/descramblingu
%w celu sprawdzenia algorytmu desynchronizacji i resynchronizacji
%UWAGA: w klasie CustomChannel domyœlnie przyjêto 21, jako liczbê bitów,
%po której nastêpuje desynch
%NALE¯Y zastanowiæ siê, czy jest to liczba odpowiednia, czy mo¿e nale¿y
%u¿yæ normy ITU/ISO, albo innej wartoœci, która przyniesie rezultaty w
%testach i pomiarach
%Choæ w zasadzie podczas testów i tak bêdzie mo¿na podaæ tê wartoœæ
%to jednak u¿ytkownik, który po prostu wyœle sygna³, a nie da konkretnej
%iloœci desynchNumOfBits, to domyœlnie jakaœ ona musi byæ tak czy siak
%Kwestia jaka powinna byæ?

fprintf("BEFORE ALL:\n");
sig = G.generateSignal();
sig.printSignal();

%fprintf("COPIED:\n");
cop = sig.copy();
%cop.printSignal();

%fprintf("SCRAMBLED:\n");
%cop = S.scrambleSignal(cop);
%cop.printSignal();

%fprintf("ENCODED:\n");
cop = Enc.encode(cop);
%cop.printSignal();

%CUSTOM CHANNEL
CC.sendSig(cop);
cop = CC.receiveSig();

%fprintf("DECODED:\n");
cop = Dec.decode(cop);
%cop.printSignal();

fprintf("AFTER ALL:\n");
%cop = D.descrambleSignal(cop);
cop.printSignal();

fprintf("BER: %f\n", H.calculateBER(sig,cop));

%mo¿na zaobserwowaæ stratê bitów
sizeOrigin = sig.getSize();
sizeCopy = cop.getSize();