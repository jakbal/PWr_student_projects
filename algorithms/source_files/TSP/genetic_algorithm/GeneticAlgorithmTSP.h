#pragma once
#include <string>
#include <iostream>
#include <fstream>

class GeneticAlgorithmTSP
{
public:
	GeneticAlgorithmTSP();

	void startGA();

	void displayGraph();									//kontrolne wyœwietlenie grafu
	void readGraphFromFile(std::string filename);			//funkcja wczytuj¹ca graf z pliku
	bool readLine(std::ifstream &file, int tab[], int size);//funkcja pomocnicza dla ww.
	bool graphExists();

	//gettery
	double getBestRoute(int d = 0);	//funckcja zwraca d³ugoœæ najlepszego znalezionego rozwi¹zania oraz kolejnoœæ wierzcho³ków
									//1 - tylko d³ugoœæ (do pomiarów lepsze)
									//2 - d³ugoœæ plus kolejnoœæ (do prezentacji lepsze)
	double getCurrentRoute(int d = 0);	//funckja zwraca rozwi¹zanie które algorytm posiada³ przez osi¹gniêciem warunku stopu
	void getParameters(); //wyœwietlenie wszystkich bie¿¹cych parametrów
	int getSizeOfPopulation() { return sizeOfPopulation; }; //gdy ustawiana bêdzie liczba rycerzy w turnieju nie powinna byæ ona wiêksza od rozmiaru populacji - walidacja w menu

	//settery
	void setNumOfIterations(int n) { numOfIterations = n; };
	void setFinalTime(int n) { finalTime = n; };
	void setSizeOfPopulation(int n); //za³o¿enie <32000 - walidacja na poziomie menu
	void setMutationProbability(double n) { mutationProbability = n; }; //walidacja przeprowadzana na poziomie menu
	void setCrossoverProbability(double n) { crossoverProbability = n; };
	void setNumOfSwaps(int n) { numOfSwaps = n; };
	void setNumOfKnights(int n) { numOfKnights = n; }

	~GeneticAlgorithmTSP();

private:
	//dane grafu:
	int numOfCities;
	int ** adjMatrix;

	//zmienne i parametry algorytmu genetycznego
	int numOfIterations;
	int finalTime;
	int sizeOfPopulation;
	double mutationProbability;
	double crossoverProbability;
	int numOfSwaps;
	int numOfKnights;

	/*STRUKTURA OSOBNIKA:
	--wektor o d³ugoœci numOfCities
	----od 0 do numOfCities-2 znajduje siê permutacja miast
	----poniewa¿ miasto 0 jest przyjmowane, jako pocz¹tkowe, dlatego nie jest uwzglêdnie w permutacji
	----st¹d iloœæ pozycji przeznaczona na permutacjê
	------na ostatniej pozycji, czyli numOfCities-1 znajduje siê wartoœæ przystosowania danego osobnika
	------przez wartoœæ przystosowania rozumiemy d³ugoœæ trasy
	------im trasa krótsza, tym osobnik jest lepiej przystosowany
	*/

	//populacje
	int ** population;
	int ** parents;
	int ** children;

	//rozwi¹zania:
    //najlepsze rozwi¹zanie - utrzymuje rozwi¹zanie najlepsze, podczas gdy rozwi¹zanie bie¿¹ce [currentOrder] mo¿e zostaæ zmienione na gorsze
	int *bestOrder;
	//bie¿¹ce rozwi¹zanie
	int *currentBestOrder;

	//funkcja wyznaczaj¹ca pocz¹tkow¹ populacjê sk³adaj¹c¹ siê z sizeOfPopulation permutacji
	void generateInitialPopulation();

	//funkcja wyznaczaj¹ca populacjê rodziców, metod¹ selekcji jest turniej
	void generateParentsPopulation();
	int tournament(); //metoda przeprowadza pojedynek numOfKnights osobników z których wy³aniany jest ten z najlepszym dopasowaniem ("wygrywa najlepszy")
					  //nastêpnie zwraca indeks na osobnika, który wygra³ turniej

	//funkcja rozmna¿aj¹ca - tworz¹ca populacjê dzieci - children
	void generateChildrenPopulation();
	void generatePairOfChildren(int index);
	void tryToMutate(int *child);
	void mutate(int *child);

	//funkcja, która zabija poprzedni¹ populacjê wprowadzaj¹c na jej miejsce now¹, czyli: population<=children
	void setNewPopulation();

	//funkcja dopasowania
	int countRouteLength(int *order);

	//funkcja zwracaj¹ca liczbê z przedzia³u [0,1]
	double getRandomProbability();

	//czyszczenie grafu
	void clearGraph();
};

