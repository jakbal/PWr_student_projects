#include "tspDynamicProgramming.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>

tspDynamicProgramming::tspDynamicProgramming()
{
	numOfCities = 0;
	ALL_PASSED = 0;
	adjMatrix = nullptr;
	DPtable = nullptr;
	Path = nullptr;
}

int tspDynamicProgramming::countPath(int node, int bitmask)
{
	//doszliœmy do ostatniego wêz³a, rozpoczynamy iœcie ruch w góre
	if (bitmask == ALL_PASSED) {
		Path[node][bitmask] = 0;
		return adjMatrix[node][0];
	}
	//je¿eli jest obliczona, to wykorzystujemy wartoœæ dla danego zbioru
	if (DPtable[node][bitmask] != -1) {
		return DPtable[node][bitmask];
	}

	//Z aktualnego wierzcho³ka idziemy do pozosta³ych wierzcho³ków nieodwiedzonych
	//wybieraj¹c drogê najlepsz¹ tj. najkrótsz¹ z dotychczasowych

	int route_length = INT_MAX;

	for (int city = 0; city < numOfCities; city++) {

		if ((bitmask&(1 << city)) == 0) {

			int new_route_length = adjMatrix[node][city] + countPath(city, bitmask | (1 << city));
			int	prev_route_length = route_length;
			route_length = std::min(route_length, new_route_length);
			if (route_length != prev_route_length) {
				Path[node][bitmask] = city;
			}
		}

	}

	return DPtable[node][bitmask] = route_length;
}

void tspDynamicProgramming::displayPath()
{
	std::cout << "Traveling Salesman's Path is: ";
	//zmienne pomocnicze
	int bitmask = 1;
	int node = 0;
	int end = (1 << numOfCities) - 1;
	//procedura wyœwietlaj¹ca minimalny cykl Hamiltona
	//na podstawie danych w tablicy Path
	std::cout << node << "->";
	do {
		std::cout << Path[node][bitmask] << "->";
		node = Path[node][bitmask];
		bitmask = (bitmask | (1 << node));
	} while (node != 0);
}

void tspDynamicProgramming::generateGraph(int n)
{
	if (n > 1) {
		clearGraph();

		numOfCities = n;
		ALL_PASSED = (1 << numOfCities) - 1;

		adjMatrix = new int *[numOfCities];
		for (int i = 0; i < numOfCities; i++) {
			adjMatrix[i] = new int[numOfCities];
		}

		//wype³nienie macierzy liczbami pseudolosowymi
		//zmienne generatora
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 50000);
		//proces wype³niania
		for (int i = 0; i < numOfCities; i++) {
			for (int j = 0; j < numOfCities; j++) {
				if (i == j)
					adjMatrix[i][j] = 0;
				else
					adjMatrix[i][j] = dist(gen);
			}
		}

		//utworzenie tablicy rekurencji
		DPtable = new int *[numOfCities];
		for (int i = 0; i < numOfCities; i++) {
			DPtable[i] = new int[(1 << numOfCities)];
		}
		//inicjalizacja DP
		for (int i = 0; i < numOfCities; i++) {
			for (int j = 0; j < (1 << numOfCities); j++) {
				DPtable[i][j] = -1;
			}
		}

		//utworzenie tablicy odtwarzaj¹cej drogê
		Path = new int *[numOfCities];
		for (int i = 0; i < numOfCities; i++) {
			Path[i] = new int[(1 << numOfCities)];
		}
		//inicjalizacja Path
		for (int i = 0; i < numOfCities; i++) {
			for (int j = 0; j < (1 << numOfCities); j++) {
				Path[i][j] = -1;
			}
		}
	}
	else {
		std::cout << "\nLiczba miast musi byc >=2.\n";
	}
}

void tspDynamicProgramming::displayGraph()
{
	for (int i = 0; i < numOfCities; i++) {
		for (int j = 0; j < numOfCities; j++) {
			std::cout << adjMatrix[i][j] << " ";
			if (j == numOfCities - 1) {
				std::cout << std::endl;
			}
		}
	}
}

void tspDynamicProgramming::loadGraphFromFile(std::string filename)
{
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
			ALL_PASSED = (1 << numOfCities) - 1;

			//utworzenie macierzy
			adjMatrix = new int *[numOfCities];
			for (int i = 0; i < numOfCities; i++) {
				adjMatrix[i] = new int[numOfCities];
			}

			int *dist = new int[numOfCities];

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

			delete []dist;

			if (adjMatrix != nullptr) {
				//Po odczytaniu liczby miast i utworzeniu macierzy s¹siedztwa
				//tworzymy tablicê rekurencji DPtable
				DPtable = new int *[numOfCities];
				for (int i = 0; i < numOfCities; i++) {
					DPtable[i] = new int[(1 << numOfCities)];
				}
				//inicjalizacja DP
				for (int i = 0; i < numOfCities; i++) {
					for (int j = 0; j < (1 << numOfCities); j++) {
						DPtable[i][j] = -1;
					}
				}
				//utworzenie tablicy Path
				Path = new int *[numOfCities];
				for (int i = 0; i < numOfCities; i++) {
					Path[i] = new int[(1 << numOfCities)];
				}
				//inicjalizacja Path
				for (int i = 0; i < numOfCities; i++) {
					for (int j = 0; j < (1 << numOfCities); j++) {
						Path[i][j] = -1;
					}
				}
			}
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

bool tspDynamicProgramming::readLine(std::ifstream & file, int tab[], int size)
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

bool tspDynamicProgramming::graphExists()
{
	return adjMatrix != nullptr;
}

tspDynamicProgramming::~tspDynamicProgramming()
{
	clearGraph();
}

void tspDynamicProgramming::clearGraph()
{
	if (adjMatrix != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			delete[] adjMatrix[i];
		}
		delete[]adjMatrix;
		adjMatrix = nullptr;
	}
	if (DPtable != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			delete[] DPtable[i];
		}
		delete []DPtable;
		DPtable = nullptr;
	}
	if (Path != nullptr) {
		for (int i = 0; i < numOfCities; i++) {
			delete[] Path[i];
		}
		delete[]Path;
		Path = nullptr;
	}

	numOfCities = 0;
	ALL_PASSED = 0;
}
