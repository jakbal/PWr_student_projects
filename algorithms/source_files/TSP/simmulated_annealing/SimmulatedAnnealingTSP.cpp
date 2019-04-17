#include "SimmulatedAnnealingTSP.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include "Timer.h"
using namespace std;

SimmulatedAnnealingTSP::SimmulatedAnnealingTSP()
{
	numOfCities = 0;
	adjMatrix = nullptr;
	bestOrder = nullptr;
	bestOrderDistance = 0;
	currentOrder = nullptr;
	currentOrderDistance = 0;
	newOrder = nullptr;
	newOrderDistance = 0;
	neighbourhood = 1;//domyœlnie ustawiane jest s¹siedztwo insert
	phi = 0;
	alpha = 0;
	L = 0;
	overTime = 0;
	temperature = 0;

	srand(time(NULL));
}

void SimmulatedAnnealingTSP::simmulateAnneal()
{
	//wyznaczenie rozwi¹zania pocz¹tkowego
	setInitialOrder();
	//wyznaczenie tempertury pocz¹tkowej
	setInitialTemperature();
	//wystartowanie licznika
	Timer *t = new Timer();
	t->startTimer();
	//kontrolna zmienna umo¿liwiaj¹ca wyœwietlanie bie¿¹cego wybiku co 1s (w przybli¿eniu)
	int workingTime = 0;

	while (t->getTime() <= overTime && temperature >= 0.000000000000001) {

		for (int i = 0; i < L; i++) {

			//wyznaczenie nowego rozwi¹zania newOrder
			if (neighbourhood == 1) insert();
			else if (neighbourhood == 2) swap();
			else if (neighbourhood == 3) invert();
			else if (neighbourhood == 4) {
				invert();
				swap();
			}

			//obliczenie d³ugoœci nowej trasy
			newOrderDistance = countRouteLength(newOrder);
			
			if (newOrderDistance < bestOrderDistance) {
				memcpy(bestOrder, newOrder, (numOfCities - 1) * 4);
				bestOrderDistance = newOrderDistance;
			}

			float delta = newOrderDistance - currentOrderDistance;

			if (delta < 0) {
				memcpy(currentOrder, newOrder, (numOfCities - 1) * 4);
				currentOrderDistance = newOrderDistance;
			}
			else if (((double)rand() / (double)RAND_MAX) < exp(-delta / temperature)) {
				memcpy(currentOrder, newOrder, (numOfCities - 1) * 4);
				currentOrderDistance = newOrderDistance;
			}

			/*if (workingTime != t->getIntTime()) {
				workingTime = t->getIntTime();
				cout << "T: " << temperature << "Wynik: " << currentOrderDistance << endl;
			}*/
		}

		if (workingTime != t->getIntTime()) {
			workingTime = t->getIntTime();
			cout << "T: " << temperature << "Wynik: " << currentOrderDistance << endl;
		}

		temperature *= alpha;
	}

	cout << "\nCzas wykonywania: " << t->getTime() << endl;

	delete t;
}

void SimmulatedAnnealingTSP::setNeighbourhood()
{
	if (neighbourhood == 1) cout << "BIEZACY TYP SASIEDZTWA - insert.\n";
	else if (neighbourhood == 2) cout << "BIEZACY TYP SASIEDZTWA - swap.\n";
	else if (neighbourhood == 3) cout << "BIEZACY TYP SASIEDZTWA - invert.\n";
	else if (neighbourhood == 4) cout << "BIEZACY TYP SASIEDZTWA - invert&swap.\n";
	cout << "Wybierz typ sasiedztwa.\n1 - insert\n2 - swap\n3 - invert\n4 - invert&swap\n";
	cout << "Wybor: ";
	int n;
	cin >> n;
	if (n >= 1 && n <= 4) {
		neighbourhood = n;
		cout << "SASIEDZTWO ZMIENIONE.\n";
	}
	else
		cout << "Nie ma takie opcji.\nSASIEDZTWO NIE ULEGO ZMIANIE.\n";
}

void SimmulatedAnnealingTSP::setParameters()
{
	cout << "BIEZACA KONFIGURACJA PARAMETROW\n\n"
		<< "phi: " << phi << endl
		<< "alpha: " << alpha << endl
		<< "liczba iteracji: " << L << endl
		<< "czas wykonywania: " << overTime << endl;

	int newPhi, newL;
	float newOverTime, newAlpha;

	cout << "\nNOWA KONFIGURACJA\n\n";
	cout << "Podaj wspolczynnik phi (T_0 = phi * DIST_0): "; cin >> newPhi;
	cout << "Podaj wspolczynnik alpha (chlodzenia) [0.00 - 0.99]: "; cin >> newAlpha;
	cout << "Podaj liczbe iteracji (dedykowana postac: n^2/4): "; cin >> newL;
	cout << "Podaj czas wykonywania (warunek stopu) [s]: "; cin >> newOverTime;

	phi = newPhi;
	alpha = newAlpha;
	L = newL;
	overTime = newOverTime;

	cout << "PARAMETRY ZMIENIONE.\n";
}

double SimmulatedAnnealingTSP::getBestRoute(int d)
{
	if (d == 1) {
		cout << "Best Length: " << bestOrderDistance << endl;
		return bestOrderDistance;
	}
	else if (d == 2) {
		cout << "Best Length: " << bestOrderDistance << endl;
		cout << "0 -> ";
		for (int i = 0; i < (numOfCities-1); i++) {
			cout << bestOrder[i] << "-> ";
		}
		cout << "0\n";
		return bestOrderDistance;
	}
	else {
		return bestOrderDistance;
	}
}

double SimmulatedAnnealingTSP::getCurrentRoute(int d)
{
	if (d == 1) {
		cout << "Current Length: " << currentOrderDistance << endl;
		return currentOrderDistance;
	}
	else if (d == 2) {
		cout << "Current Length: " << currentOrderDistance << endl;
		cout << "0 -> ";
		for (int i = 0; i < (numOfCities - 1); i++) {
			cout << currentOrder[i] << "-> ";
		}
		cout << "0\n";
		return currentOrderDistance;
	}
	else {
		return currentOrderDistance;
	}
}

void SimmulatedAnnealingTSP::displayGraph()
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

void SimmulatedAnnealingTSP::readGraphFromFile(std::string filename)
{
	clearGraph();

	std::ifstream file;
	int cities[1];
	file.open(filename.c_str());

	//wczytanie grafu z pliku
	if (file.is_open()) {
		//jezeli nazwa pliku jest poprawna, to poprzedni graf zostaje usuniety
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

			bestOrder = new int[numOfCities - 1];
			currentOrder = new int[numOfCities - 1];
			newOrder = new int[numOfCities - 1];
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

bool SimmulatedAnnealingTSP::readLine(std::ifstream & file, int tab[], int size)
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

bool SimmulatedAnnealingTSP::graphExists()
{
	return adjMatrix != nullptr;;
}

void SimmulatedAnnealingTSP::test()
{
	setInitialOrder();

	for (int i = 0; i < numOfCities - 1; i++) {
		cout << currentOrder[i] << " ";
	}
	cout << endl;
	cout << currentOrderDistance;
	cout << endl;
}

SimmulatedAnnealingTSP::~SimmulatedAnnealingTSP()
{
	clearGraph();
}

void SimmulatedAnnealingTSP::setInitialOrder()
{
	//wersja najprostsza
	/*
	for (int i = 1; i < numOfCities; i++) {
		currentOrder[i - 1] = i;
	}
	currentOrderDistance = countRouteLength(currentOrder);

	memcpy(bestOrder, currentOrder, (numOfCities - 1) * 4);
	bestOrderDistance = currentOrderDistance;*/
	
	//wersja zach³anna

	//tablica które wierzcho³ki w³¹czono
	bool *isUsed = new bool[numOfCities];
	for (int i = 0; i < numOfCities; i++) {
		isUsed[i] = false;
	}

	int index_1, index_2;//indeks wierzcho³ka do którego idziemy z zera
	int min = INT_MAX;

	//po³¹czenie 0->x
	//wyznaczenie pierwszego wierzcho³ka w currentOrder
	//czyli po³¹czenia z wierz zerowego do wierzcho³ka currentOrder[0]
	for (int i = 1; i < numOfCities; i++) {
		if (adjMatrix[0][i] < min) {
			min = adjMatrix[0][i];
			index_1 = i;
		}
	}

	isUsed[index_1] = true;	//oznaczenie wierzcho³ka jako wyokrzystanego
	currentOrder[0] = index_1;//dodanie wierzcho³ka na pierwsz¹ pozycjê current Order

	//po³¹czenia x->y
	for (int i = 2; i < numOfCities; i++) {
		min = INT_MAX;
		for (int j = 1; j < numOfCities; j++) {
			if (!isUsed[j] && j != index_1 && adjMatrix[index_1][j] < min) {
				min = adjMatrix[index_1][j];
				index_2 = j;
			}
		}
		isUsed[index_2] = true;
		currentOrder[i-1] = index_2;
		index_1 = index_2;
	}

	currentOrderDistance = countRouteLength(currentOrder);

	memcpy(bestOrder, currentOrder, (numOfCities - 1) * 4);
	bestOrderDistance = currentOrderDistance;
}

void SimmulatedAnnealingTSP::setInitialTemperature()
{
	temperature = phi * currentOrderDistance;
}

void SimmulatedAnnealingTSP::insert()
{
	int i, j;//i ma byc mniejsze a j wiekszym indeksem
	do {
		i = rand() % (numOfCities - 1);
		j = rand() % (numOfCities - i - 1) + i;//zapewni to ¿e j>=i
	} while (i == j);//nie chcemy wylosowaæ dwóch takich samych indeksów

	memcpy(newOrder, currentOrder, (numOfCities - 1) * 4);

	int k = newOrder[i];

	for (i; i < j; i++) {
		newOrder[i] = newOrder[i + 1];
	}

	newOrder[j] = k;
}

void SimmulatedAnnealingTSP::swap()
{
	int i, j;
	do {
		i = rand() % (numOfCities - 1);
		j = rand() % (numOfCities - 1);
	} while (i==j);

	memcpy(newOrder, currentOrder, (numOfCities - 1) * 4);

	int k = newOrder[i];
	newOrder[i] = newOrder[j];
	newOrder[j] = k;
}

void SimmulatedAnnealingTSP::invert()
{
	int i, j;//i ma byc mniejsze a j wiekszym indeksem
	do {
		i = rand() % (numOfCities - 1);
		j = rand() % (numOfCities - i-1) + i;//zapewni to ¿e j>=i
	} while (i == j);

	memcpy(newOrder, currentOrder, (numOfCities - 1) * 4);

	int k;
	while (i < j) {
			k = newOrder[j];
			newOrder[j] = newOrder[i];
			newOrder[i] = k;
			i++;
			j--;
	}
}

int SimmulatedAnnealingTSP::countRouteLength(int * order)
{
	int dist = 0;

	dist += adjMatrix[0][order[0]];
	
	for (int i = 0; i < (numOfCities - 2); i++) {
		dist += adjMatrix[order[i]][order[i + 1]];
	}
	
	dist += adjMatrix[order[(numOfCities - 2)]][0];

	return dist;
}

void SimmulatedAnnealingTSP::clearGraph()
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
	if (bestOrder != nullptr) {
		delete[]bestOrder;
		bestOrder = nullptr;
		bestOrderDistance = 0;
		// << "BO usuniety.\n";
	}
	if (currentOrder != nullptr) {
		delete[]currentOrder;
		currentOrder = nullptr;
		currentOrderDistance = 0;
		//cout << "CO usuniety.\n";
	}
	if (newOrder != nullptr) {
		delete[]newOrder;
		newOrder = nullptr;
		newOrderDistance = 0;
		//cout << "NO usuniety.\n";
	}
}
