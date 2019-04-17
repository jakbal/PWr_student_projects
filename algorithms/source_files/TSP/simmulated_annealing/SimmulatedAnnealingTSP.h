#pragma once
#include <string>
#include <iostream>
#include <fstream>

class SimmulatedAnnealingTSP
{
public:
	SimmulatedAnnealingTSP();

	void simmulateAnneal();//parametr n odpowiada za wybór typu s¹sziedztwa
									//1 - swap
									//N\{1} - invert

	void setNeighbourhood();
	void setParameters();			//funkcja wyswietla bie¿¹ce parametry oraz umo¿liwia ustawienie nowych
	double getBestRoute(int d = 0);	//funckcja zwraca d³ugoœæ najlepszego znalezionego rozwi¹zania oraz kolejnoœæ wierzcho³ków
									//1 - tylko d³ugoœæ (do pomiarów lepsze)
									//2 - d³ugoœæ plus kolejnoœæ (do prezentacji lepsze)
	double getCurrentRoute(int d = 0);	//funckja zwraca rozwi¹zanie które algorytm posiada³ przez osi¹gniêciem warunku stopu

	void displayGraph();									//kontrolne wyœwietlenie grafu
	void readGraphFromFile(std::string filename);			//funkcja wczytuj¹ca graf z pliku
	bool readLine(std::ifstream &file, int tab[], int size);//funkcja pomocnicza dla ww.
	bool graphExists();										//funkcja zwraca informacje o istnieniu grafu

	void test();

	~SimmulatedAnnealingTSP();
private:
	//dane grafu:
	int numOfCities;
	int ** adjMatrix;

	//rozwi¹zania:
	//najlepsze rozwi¹zanie - utrzymuje rozwi¹zanie najlepsze, podczas gdy rozwi¹zanie bie¿¹ce [currentOrder] mo¿e zostaæ zmienione na gorsze
	int *bestOrder;
	int bestOrderDistance;
	//bie¿¹ce rozwi¹zanie
	int *currentOrder;
	int currentOrderDistance;
	//nowe rozwi¹zanie po perturbacji - s¹siedztwo typu swap lub typu invert
	int *newOrder;
	int newOrderDistance;
	
	//typ s¹siedztwa
	int neighbourhood; // 1 - swap 2 - invert

	//parametry algorytmu:
	float phi;			//sta³a s³u¿¹ca do wyznaczenia temperatury pocz¹tkowej
	float alpha;		//wspó³czynnik ch³odzenia
	float L;				//liczba iteracji
	float overTime;		//warunek stopu, czas w sekundach
	float temperature;  //temperatura metalu

	//wyzanczenie rozwi¹zania pocz¹tkowego -> bestOrder,currentOrder oraz 2x[...]OrderDistance
	//metod¹ zach³ann¹
	void setInitialOrder();
	//wyznaczenie temperatury pocz¹tkowej
	void setInitialTemperature();
	//wyznaczenie nowego rozwi¹zania -> newOrder
	void insert();
	void swap();
	void invert();
	//wyznaczenie d³ugoœci trasy
	int countRouteLength(int *order);

	//czyszczenie grafu
	void clearGraph();
};

