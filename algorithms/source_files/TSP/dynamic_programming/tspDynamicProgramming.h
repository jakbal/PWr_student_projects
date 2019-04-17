#pragma once
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>

class tspDynamicProgramming
{
public:
	tspDynamicProgramming();
	int countPath(int node = 0, int bitmask = 1);	//metoda obliczaj¹ca d³ugoœæ minimalnego cyklu Hamiltona
													//node - aktualny wêze³ z którego idziemy dalej
													//bitmask - reprezentacja zbioru miniêtych miast
	void displayPath();								//metoda wyœwietlaj¹ca minimalny cykl Hamiltona
													//display path --> spróbwaæ u¿yæ analogicznie tablicy jednowymiarowej 1x2^n
	void generateGraph(int n);						//generacja grafu, gdzie n - liczba miast

	void displayGraph();							//wyœwietlenie grafu - funkcja do kontroli - nie do³¹czona do MENU testowego

	void loadGraphFromFile(std::string filename);				//wczytywanie grafu z pliku
	bool readLine(std::ifstream &file, int tab[], int size);	//funckja pomocnicza dla ww.

	bool graphExists();			//zapobieganie b³êdom wywo³ania countPath(), gdy graf nie istnieje

	~tspDynamicProgramming();	//destruktor wywo³uje clearGraph()
private:
	//atrybuty grafu
	int numOfCities;	//liczba miast
	int **adjMatrix;	//macierz s¹siedztwa

	//zmienne do algorytmu
	int **DPtable;	//tablica rekurencji
	int **Path;		//tablica do odtworzenia drogi
	static const int INF = INT_MAX;
	int ALL_PASSED; //wartoœæ maski bitowej odpowiadaj¹ca zbiorowi, w którym wszytskie wierzcho³ki zosta³y ju¿ sprawdzone
					//ALL_PASSED = 1(0)...1(N-1) 

	void clearGraph();
};

