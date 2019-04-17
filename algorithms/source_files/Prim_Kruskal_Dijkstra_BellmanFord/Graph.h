#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "adjList.h"
#include "Queue.h"
using namespace std;


class Graph
{
public:
	Graph();

	int ** adjMatrix = nullptr;	//macierz s¹siedztwa
	adjList * list = nullptr;   //tablica list s¹siedztwa

	int V;
	int E;
	int firstV;
	int lastV;
	static const int INF = INT_MAX;
	static const int INF_BF = 1000000;
	
	//UWAGA
	//Wywo³anie algorytmu Dijsktry lub Bellmana-Forda z arg. domyœlnym
	//uruchamia dany algorytm z wierzcho³kiem firstV

	//ALGORYTM PRIMA
	void primMatrix(int root);
	void primList(int root);

	//ALGORYTM KRUSKALA
	void kruskalMatrix(int root);
	void kruskalList(int root);

	//ALGORYTM DIJKSTRY
	void dijkstraMatrix(int s = -1);
	void dijkstraList(int s = -1);

	//ALGORYTM BELLMANA-FORDA
	void bellmanfordMatrix(int s = -1);
	void bellmanfordList(int s = -1);

	//ALGORYTM PRIMA - prezentacja wyników
	void printMSTMatrix(int *parent);
	void printMSTList(int *parent);

	//ALGORYTM KRUSKALA - prezentacja wyników
	void printMST(queueElement **MST, int e);

	//ALGORYTM DIJKSTRY & BELLMANA-FORDA - prezentacja wyników
	void printSP(int *parent, int *distance, int s);
	void printPath(int *parent, int s, int v);

	//Dla algorytmów z problemu MST operuj¹cych na macierzy
	//zosta³y zaimplementowane poni¿sze dwie metody
	//zastêpuj¹ce kolejkê priorytetow¹ Q

	//funckja dodatkowa dla alg Prima rep macierzowej
	int minKey(bool *mst, int *keys);
	//funkcja dodatkowa dla alg Dijkstry rep macierzowej
	int minDis(int *distance, bool *Set);


	void createEmptyAdjMatrix();						//funkcja tworzy macierz zer o rozmairze [V][V]
														//V musi byæ ju¿ znane
	void createList();									//funkcja tworzy listê s¹siedztwa na podstawie macierzy s¹siedztwa
														//jezeli macierz jest pusta oznacza to, ¿e graf jest pusty,
														//wiec lista nie zostanie utworzona

	//dwa generatory grafów o podanej gêstoœci
	//odpowiednio grafu nieskierowanego i skierowanego
	//przyjêto, ¿e wagi losowane bêd¹ z przedzia³u [1, 1M] gdy¿ jest to przedzia³ wystarczaj¹cy
	//dla przeprowadzanych testów, gdzie liczba wierzcho³ków maksymalnie wynosiæ bêdzie 1000
	//bior¹c pod uwage ¿e dla odpowiedniej gêstoœci istnieje wiele œcie¿ek, a algorytm i tak musi sprawdziæ wszystkie.
	void generateUndirectedGraph(int v, int d);			//v - liczba wierzcho³ków w grafie - >0
	void generateDirectedGraph(int v, int d);			//d - gêstoœæ grafu wyra¿ana w procentach 0 - 100

	void readUndirectedGraphFromFile(string filename);	//wczytanie grafu nieskierowanego z pliku .txt
	void readDirectedGraphFromFile(string filename);    //wczytanie grafu skierowanego z pliku .txt
	bool readLine(ifstream &file, int tab[], int size); //pomocnicza funckja
														//funkcje wg SDIZO_time.pdf

	void printAdjMatrix();								//funkcje kontrolne, wyœwietlaj¹ce strukturê grafu
	void printAdjList();

	void clearGraph();									//usuwa aktualnie przechowywany graf
														//usuwa macierz i listê s¹siedztwa oraz zeruje dane takie jak V,E
														//pierwszy i ostatni wierzcho³ek ustawia na wartoœci -1

	~Graph();
};

