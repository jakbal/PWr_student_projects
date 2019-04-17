#pragma once
#include "GeneticAlgorithmTSP.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include "Timer.h"
using namespace std;

GeneticAlgorithmTSP::GeneticAlgorithmTSP()
{
	//startowe wartoœci parametrów
	numOfCities = 0;

	numOfIterations = 100;
	finalTime = 15;
	sizeOfPopulation = 100;
	mutationProbability = 0.01; //wartosci p-p ustawione wg instrukcji
	crossoverProbability = 0.8;
	numOfSwaps = 1;
	numOfKnights = 10;

	adjMatrix = nullptr;

	bestOrder = nullptr;
	currentBestOrder = nullptr;

	population = nullptr;
	parents = nullptr;
	children = nullptr;

	srand(time(NULL));
}

void GeneticAlgorithmTSP::startGA()
{
	//zmienna iteracyjna
	int iteration = 0;
	//stoper
	Timer *t = new Timer();
	t->startTimer();
	int workingTime = 0;

	//generacja populacji pocz¹tkowej oraz wyniku jaki jest najlepszy na pocz¹tku
	generateInitialPopulation();
	cout << "Wynik: " << getCurrentRoute() << endl;

	while (t->getTime() <= finalTime && iteration < numOfIterations) {

		generateParentsPopulation();  //generacja populacji rodziców
		generateChildrenPopulation(); //generacja dzieci z wybranej populacji rodziców
		setNewPopulation();			  //zamiana pokoleñ population<=children
		//co 1s wyswietl bie¿¹cy najlepszy wynik
		if (workingTime != t->getIntTime()) {
			workingTime = t->getIntTime();
			cout << "Wynik: " << getCurrentRoute() << endl;
		}
		iteration++;
	}

	cout << "\nCzas wykonywania: " << t->getTime() << endl;
	cout << "Najlepszy wynik: " << getBestRoute() << endl;
	delete t;
}

void GeneticAlgorithmTSP::displayGraph()
{
	if (adjMatrix != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			for (int j = 0; j < numOfCities; j++) {
				std::cout << adjMatrix[i][j] << " ";
				if (j == numOfCities - 1) {
					std::cout << std::endl;
				}
			}
		}

		cout << "\nLiczba miast: " << numOfCities << endl;
	}
	else {
		cout << "Macierz sasiedztwa jest pusta.\n";
	}
}

void GeneticAlgorithmTSP::readGraphFromFile(std::string filename)
{
	std::ifstream file;
	int cities[1];
	file.open(filename.c_str());

	//wczytanie grafu z pliku
	if (file.is_open()) {
		//jezeli nazwa pliku jest poprawna, to poprzedni graf zostaje usuniety
		//w.p.w. nie ma sensu usuwaæ istniej¹cego grafu
		//zak³ada siê poprawnoœæ struktury danych w pliku
		clearGraph();

		if (readLine(file, cities, 1)) {

			//wczytanie i inicjalzacja podstawowych danych
			numOfCities = cities[0];

			//utworzenie macierzy
			adjMatrix = new int *[numOfCities];
			for (int i = 0; i < numOfCities; i++) {
				adjMatrix[i] = new int[numOfCities];
			}

			//wektor przechowuj¹cy wiersz macierzy
			int *dist = new int[numOfCities];

			//wczytanie macierzy s¹siedztwa z pliku
			for (int i = 0; i < numOfCities; i++) {
				if (readLine(file, dist, numOfCities)) {
					for (int j = 0; j < numOfCities; j++) {
						adjMatrix[i][j] = dist[j];
					}
				}
				else {
					std::cout << "\nFILE ERROR - EDGE\n";
				}
			}

			delete[]dist;

			//utworzenie trzech populacji
			population = new int *[sizeOfPopulation];
			for (int i = 0; i < sizeOfPopulation; i++) {
				population[i] = new int[numOfCities];
			}
			parents = new int *[sizeOfPopulation];
			for (int i = 0; i < sizeOfPopulation; i++) {
				parents[i] = new int[numOfCities];
			}
			children = new int *[sizeOfPopulation];
			for (int i = 0; i < sizeOfPopulation; i++) {
				children[i] = new int[numOfCities];
			}
			//oraz dwóch rozwi¹zañ
			bestOrder = new int[numOfCities];
			currentBestOrder = new int[numOfCities];
		}
		else {
			std::cout << "\nFILE ERROR - INFO\n";
		}

		file.close();

	}
	else {
		std::cout << "\nFILE ERROR - OPEN\n";
	}
}

bool GeneticAlgorithmTSP::readLine(std::ifstream & file, int tab[], int size)
{
	std::string s;
	getline(file, s);
	if (file.fail() || s.empty())
		return false;
	std::istringstream in_ss(s);
	for (int i = 0; i < size; i++) {
		in_ss >> tab[i];
		if (in_ss.fail())
			return false;
	}
	return true;
}

bool GeneticAlgorithmTSP::graphExists()
{
	return adjMatrix != nullptr;
}

double GeneticAlgorithmTSP::getBestRoute(int d)
{
	if (d == 1) {
		cout << "Best Length: " << bestOrder[numOfCities - 1] << endl;
		return bestOrder[numOfCities - 1];
	}
	else if (d == 2) {
		cout << "Best Length: " << bestOrder[numOfCities - 1] << endl;
		cout << "0 -> ";
		for (int i = 0; i < (numOfCities - 1); i++) {
			cout << bestOrder[i] << "-> ";
		}
		cout << "0\n";
		return bestOrder[numOfCities - 1];
	}
	else {
		return bestOrder[numOfCities - 1];
	}
}

double GeneticAlgorithmTSP::getCurrentRoute(int d)
{
	if (d == 1) {
		cout << "Current Length: " << currentBestOrder[numOfCities - 1] << endl;
		return currentBestOrder[numOfCities - 1];
	}
	else if (d == 2) {
		cout << "Current Length: " << currentBestOrder[numOfCities - 1] << endl;
		cout << "0 -> ";
		for (int i = 0; i < (numOfCities - 1); i++) {
			cout << currentBestOrder[i] << "-> ";
		}
		cout << "0\n";
		return currentBestOrder[numOfCities - 1];
	}
	else {
		return currentBestOrder[numOfCities - 1];
	}
}

void GeneticAlgorithmTSP::getParameters()
{
	cout << "BIEZACA KONFIGURACJA PARAMETROW\n\n"
		<< "rozmiar populacji: " << sizeOfPopulation << endl
		<< "liczba osobnikow w turnieju: " << numOfKnights << endl
		<< "prawdopodobienstwo krzyzowania: " << crossoverProbability << endl
		<< "prawdopodobienstwo mutacji: " << mutationProbability << endl
		<< "liczba iteracji: " << numOfIterations << endl
		<< "liczba mutowanych genow: " << numOfSwaps << endl
	    << "czas dzialania [s]: " << finalTime << endl;
}

void GeneticAlgorithmTSP::setSizeOfPopulation(int n)
{
	if (n % 2 == 1) n++; //jeœli u¿ytkownik poda³ nieparzyst¹ liczb¹ to zwiêkszamy j¹ o jeden
						 //parzysty rozmiar populacji jest niezbênym za³o¿eniem dla funkcji generuj¹cej parê dzieci
						 //poniewa¿ zawsze generowana jest para, czyli liczba dzieci bêdzie parzystac
						 //na³o¿enie takiego ograniczenia jest najprostszym rozwi¹zaniem tego problemu
						 //a jednoczeœnie jeden osobnik wiêcej nie jest, a¿ tak znacz¹c¹ ingerencja w dzia³anie algorytmu,
						 //który opiera siê tak¿e w³aœnie na odpowiednio du¿ym ROZMIARZE populacji

	//po upewnieniu siê, ¿e n jest parzysta, mo¿na zmieniæ rozmiar populacji
	if (graphExists()) {
		//zmieniaj¹c rozmiar populacji musimy usun¹æ to co by³o
		if (population != nullptr) {
			for (int i = 0; i < sizeOfPopulation; i++) {
				delete[] population[i];
			}
			delete[]population;
			population = nullptr;
			//cout << "Graf usuniety.\n";
		}
		if (parents != nullptr) {
			for (int i = 0; i < sizeOfPopulation; i++) {
				delete[] parents[i];
			}
			delete[]parents;
			parents = nullptr;
			//cout << "Graf usuniety.\n";
		}
		if (children != nullptr) {
			for (int i = 0; i < sizeOfPopulation; i++) {
				delete[] children[i];
			}
			delete[]children;
			children = nullptr;
			sizeOfPopulation = 0;
			//cout << "Graf usuniety.\n";
		}

		//wtedy mo¿emy zmieniæ rozmiar populacji
		sizeOfPopulation = n;

		//a nastêpnie ponownie utworzyæ populacje
		//utworzenie trzech populacji
		population = new int *[sizeOfPopulation];
		for (int i = 0; i < sizeOfPopulation; i++) {
			population[i] = new int[numOfCities];
		}
		parents = new int *[sizeOfPopulation];
		for (int i = 0; i < sizeOfPopulation; i++) {
			parents[i] = new int[numOfCities];
		}
		children = new int *[sizeOfPopulation];
		for (int i = 0; i < sizeOfPopulation; i++) {
			children[i] = new int[numOfCities];
		}
	}
	else {
		//jezeli graf nie istnieje to znaczy, ¿e jest to pierwsze uruchomienie programu
		//zatem nie mo¿emy dublowaæ alokacji miejsca, która odbêdzie siê i tak w momencie wczytywania grafu
		//wówczas potrzeba tylko rozmiaru populacji
		//na górze, kiedy graf istnieje a my zmieniamy rozmiar populacji, to trzeba usun¹æ istniej¹ce trzy populacje
		//a nastêpnie utworzyæ nowe w miêdzy czassie ustawiaj¹c nowy rozmiar populacji
		//gdybyœmy ponownie wczytywali graf z pliku, to nie ma problemu, bo i tak na pocz¹tku robimy clearGraph(),
		//wiêc potem znów utworzymy 3 populacje rozmiaru takiego, jaki by³ uprzednio ustawiony.
		sizeOfPopulation = n;
	}
}

GeneticAlgorithmTSP::~GeneticAlgorithmTSP()
{
	clearGraph();
}

void GeneticAlgorithmTSP::generateInitialPopulation()
{
	//wszystkie osobniki startowe to permutacje 1,2,3,..., n-2, n-1
	for (int i = 0; i < sizeOfPopulation; i++) {
		for (int j = 1; j < numOfCities; j++) {
			population[i][j - 1] = j;
		}
	}
	//w ka¿dym osobniku dokonujemy losowych zmian - generujemy nowe permutacje
	//nastêpnie obliczamy dla ka¿dego wartoœæ funkcji przystosowania
	int m, n, k;
	for (int i = 0; i < sizeOfPopulation; i++) {
		//M1
		for (int j = 0; j < numOfCities; j++) {
			//wylosuj dwie pozycje
			do {
				m = rand() % (numOfCities - 1);
				n = rand() % (numOfCities - 1);
			} while (m == n);
			//zamieñ je miejscami
			k = population[i][m];
			population[i][m] = population[i][n];
			population[i][n] = k;
		}
		/*M2
		for (int j = 0; j < (numOfCities - 1); j++) {
			int delta = rand() % (numOfCities - 1 - j);
			int temp = population[i][j];
			population[i][j] = population[i][j + delta];
			population[i][j + delta] = temp;
		}*/
		population[i][numOfCities-1] = countRouteLength(population[i]);
	}

	//wyznaczenie najlepszego rozwi¹zania w populacji pocz¹tkowej
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < sizeOfPopulation; i++) {
		if (population[i][numOfCities - 1] < min) {
			min = population[i][numOfCities - 1];
			index = i;
		}
	}

	memcpy(bestOrder, population[index], numOfCities * 4);
	memcpy(currentBestOrder, population[index], numOfCities * 4);
}

void GeneticAlgorithmTSP::generateParentsPopulation()
{
	for (int i = 0; i < sizeOfPopulation; i++) {
		int indexOfWinner = tournament();	//indeks zwyciêzcy
		memcpy(parents[i], population[indexOfWinner], numOfCities * 4);	//zwyciêzca jest wstawiany na pozycjê i-t¹ do populacji rodziców
	}
}

int GeneticAlgorithmTSP::tournament()
{
	//u¿ycie maszyny mt generuje bardzo du¿y nak³ad czasowy
	//dla pewnej instancji mt - 45s a rand() - 16s
	//jednak u¿ycie funkcji rand() nie pozwoli na posiadanie populacji wiêkszej, ni¿ 32000,
	//gdy¿ nie bêdziemy w stanie wylosowaæ liczby >32000, zatem osobniki takie jak np. 50000 bêd¹ pomijane
	//drugie podejœcie to na³o¿enie ograniczeñ na rozmiar populacji, nie mo¿na ustawiæ rozmiaru >32000,
	//wówczas zyskujemy prêdkoœæ dzia³ania algorytmu
	//drugie podejœcie zosta³o wybrane

	//int val;
	//random_device rd;
	//mt19937 gen(rd());
	//uniform_int_distribution<> dist(0, (sizeOfPopulation - 1));

	int indexOfWinner;
	int vffOfWinner;
	//indexOfWinner = dist(gen); //pierwszy wybrany osobnik jest domniemanym zwyciêzc¹
	indexOfWinner = rand() % sizeOfPopulation; //zbyt ma³y przedzial 0-32000
	vffOfWinner = population[indexOfWinner][numOfCities - 1]; //wartoœæ jego funkcji dopasowania staje sie odnoœnikiem
	
	int index;
	//pojedynek przeprowadzamy numOfKnights razy
	for (int i = 0; i < numOfKnights; i++) {
		//osobnik nie mo¿e rywalizowac z samym sob¹
		do {
			//index = dist(gen);
			index = rand() % sizeOfPopulation;
		} while (index == indexOfWinner);
		//powy¿sza pêtla dopuszcza pojedynek powtórny pomiêdzy dwoma osobnikami
		//nie ma ¿adnej listy tabu wybieranych osobników
		//szansa powtórzenia liczby to 0.000031 zatem mo¿na za³o¿yæ, ¿e liczby losowane
		//bêd¹ powtarzaæ siê rzadko
		if (population[index][numOfCities - 1] < vffOfWinner) {
			vffOfWinner = population[index][numOfCities - 1];
			indexOfWinner = index;
		}
	}

	//na koniec pojedynku w indexOfWinner znajduje siê indeks zwyciêzcy
	return indexOfWinner;
}

void GeneticAlgorithmTSP::generateChildrenPopulation()
{
	for (int i = 0; i < sizeOfPopulation; i = i + 2) {
		generatePairOfChildren(i);
	}
}

void GeneticAlgorithmTSP::generatePairOfChildren(int index)
{
	//wybierz dwóch rodziców
	int m, n;
	do {
		m = rand() % (sizeOfPopulation);
		n = rand() % (sizeOfPopulation);
	} while (m == n);
	int *p1 = parents[m];
	int *p2 = parents[n];
	//utwórz dwójkê dzieci i sklonuj do nich genotyp rodziców
	int *c1 = new int[numOfCities];
	int *c2 = new int[numOfCities];
	memcpy(c1, p1, numOfCities * 4);
	memcpy(c2, p2, numOfCities * 4);
	//wybierz dwa punkty krzy¿owania (m ma byæ < n)
	do {
		m = rand() % (numOfCities - 1);
		n = rand() % (numOfCities - 1);
	} while (m == n);
	//sprawdz poprawnoœæ punktów - aby zawsze m by³ tym bli¿ej pocz¹tku a n tym bli¿ej koñca
	if (m > n) {
		int k = n;
		n = m;
		m = k;
	}
	//implementowane jest krzy¿owanie PMX z dwoma punktami ciêcia
	//z penym p-p przeprowadz krzy¿owanie na pierwszym dziecku
	if (getRandomProbability() <= crossoverProbability) {
		//dzia³amy w przedziale wyznaczonym przez punkty krzy¿owania
		for (int i = m; i <= n; i++) {
			//chc¹ wstawiæ na pozycjê i-t¹ wartoœæ z rodzica p2[i], musimy odnaleŸæ tê wartoœæ w dziecku c1
			//a nastêpnie dokonaæ zamiany swap pomiêdzy pozycj¹ c1[i], gdzie znajduje siê pewna wartoœæ X oraz pozycj¹ gdzie znajduje siê w c1 wartoœæ równa p2[i]
			//gdyby zrobiæ od razu c1[i]=p2[i], to gubimy wartoœæ z tej pozycji oraz tworzymy cykl oraz nie odwiedzamy wszystkich miast
			for (int k = 0; k < (numOfCities - 1); k++) {
				if (c1[k] == p2[i]) {
					c1[k] = c1[i];
					break;
				}
			}
			c1[i] = p2[i];//na dana pozycjê przekopiuj gen rodzica
		}
	}
	//z pewnym innym p-p przeprowadz krzy¿owanie na drugim dziecku
	if (getRandomProbability() <= crossoverProbability) {
		for (int i = m; i <= n; i++) {
			for (int k = 0; k < (numOfCities - 1); k++) {
				if (c2[k] == p1[i]) {
					c2[k] = c2[i];
					break;
				}
			}
			c2[i] = p1[i];
		}
	}
	//spróbuj dokonaæ mutacji na pierwszym dziecku
	tryToMutate(c1);
	//spróbuj odkonac mutacji na drugim dziecku
	tryToMutate(c2);
	//oblicz now¹ wartoœæ funkcji przystosowania dla obu dzieci
	c1[numOfCities - 1] = countRouteLength(c1);
	c2[numOfCities - 1] = countRouteLength(c2);
	//po tych czynnoœciach wpisz dzieci do populacji children na miejsca index oraz index+1 --- memcpy kopiuje zawartoœæ
	//w zewnêtrznej pêtli poruszamy siê po indeksach parzystych 0, 2, 4
	//gdy n=100 to pêtla wykona siê jeszcze dla 98, wiêc znajdziemy dzieci na pozycje 98 oraz 99, czyli otrzymamy 100 dzieci
	//pojawia siê tu problem z nieparzystoœci¹ populacji, dlatego parzystoœæ populacji jest za³o¿eniem
	//w menu kontekstowym nale¿y zabezpieczyæ tak¹ sytuacjê, jeœli u¿ytkownik bêdzie chcia³ podaæ liczbê nieparzyst¹, to nale¿y j¹ zwiêkszyæ o 1
	memcpy(children[index], c1, numOfCities * 4);
	memcpy(children[index + 1], c2, numOfCities * 4);
	//ca³kowicie bezpiecznie usun obiekty tymczasowych dzieci, rodziców nie usuwamy, bo te wskaŸniki tylko pomocnie wskazywa³y na odpowiedni miejsca w populacji rodziców
	delete[]c1;
	delete[]c2;
}

void GeneticAlgorithmTSP::tryToMutate(int * child)
{
	if (getRandomProbability() <= mutationProbability)
		mutate(child);
}

void GeneticAlgorithmTSP::mutate(int * child)
{
	int m, n, k;
	for (int i = 0; i < numOfSwaps; i++) {
		//wylosuj dwa ró¿ne pojedyncze geny
		do {
			m = rand() % (numOfCities - 1);
			n = rand() % (numOfCities - 1);
		} while (m == n);
		//zamieñ je miejscami
		k = child[m];
		child[m] = child[n];
		child[n] = k;
		//mutacja powinna byc jak njabardziej subtelna
	}
}

void GeneticAlgorithmTSP::setNewPopulation()
{
	//przeniesienie populacji dzieci na miejsce nowej populacji
	for (int i = 0; i < sizeOfPopulation; i++) {
		memcpy(population[i], children[i], numOfCities * 4);
	}
	//aktualizacja rozwi¹zañ wpierw bie¿¹cego i jeœli uleg³o polepszeniu, to tak¿e najlepszego ze wszytskich
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < sizeOfPopulation; i++) {
		if (population[i][numOfCities - 1] < min) {
			min = population[i][numOfCities - 1];
			index = i;
		}
	}
	//przekopiuj najlepsze bie¿¹ce rozwi¹zanie
	memcpy(currentBestOrder, population[index], numOfCities * 4);
	//jesli jest ono lepsze ni¿ najlepsze, to przekopiuj je do najlepszego
	if (currentBestOrder[numOfCities - 1] < bestOrder[numOfCities - 1])
		memcpy(bestOrder, currentBestOrder, numOfCities * 4);
}

int GeneticAlgorithmTSP::countRouteLength(int * order)
{
	int dist = 0;

	dist += adjMatrix[0][order[0]];

	for (int i = 0; i < (numOfCities - 2); i++) {
		dist += adjMatrix[order[i]][order[i + 1]];
	}

	dist += adjMatrix[order[(numOfCities - 2)]][0];

	return dist;
}

double GeneticAlgorithmTSP::getRandomProbability()
{
	return (double)rand() / (double)RAND_MAX;
}

void GeneticAlgorithmTSP::clearGraph()
{
	if (adjMatrix != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			delete[] adjMatrix[i];
		}
		delete[]adjMatrix;
		adjMatrix = nullptr;
		numOfCities = 0;
		//cout << "Graf usuniety.\n";
	}
	if (population != nullptr) {
		for (int i = 0; i < sizeOfPopulation; i++) {
			delete[] population[i];
		}
		delete[]population;
		population = nullptr;
		//cout << "Graf usuniety.\n";
	}
	if (parents != nullptr) {
		for (int i = 0; i < sizeOfPopulation; i++) {
			delete[] parents[i];
		}
		delete[]parents;
		parents = nullptr;
		//cout << "Graf usuniety.\n";
	}
	if (children != nullptr) {
		for (int i = 0; i < sizeOfPopulation; i++) {
			delete[] children[i];
		}
		delete[]children;
		children = nullptr;
		//cout << "Graf usuniety.\n";
	}
	if (bestOrder != nullptr) {
		delete[]bestOrder;
		bestOrder = nullptr;
		// << "BO usuniety.\n";
	}
	if (currentBestOrder != nullptr) {
		delete[]currentBestOrder;
		currentBestOrder = nullptr;
		//cout << "CO usuniety.\n";
	}
}
