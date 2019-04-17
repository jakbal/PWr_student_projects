#pragma once
#include "queueElement.h"
class Queue
{
public:
	Queue(int capacity);
	int size;
	int capacity;
	queueElement ** Q = nullptr;			   //kolejka, tablica o dlugosci capacity (ilosci wierzcho³ków), przechowuj¹ca wskaŸniki na obiekty typu queueElement

	void insertNode(int v, int key);		   //dodanie nowego elementu do kopcja
	void insertEdge(int u, int v, int key);	   //funkcja dla algorytmu Prima - heapsort (przynajmniej coœ ala)
	int  extractRoot();						   //funkcja zwraca korzeñ kolejki (kopca typu min)
	int* extractEdge();						   //funkcja zwraca tablice z wartosciami (u,v,w) w tej kolejnoœci	
	void minHeapify(int index, int direction); //przywracanie wlasnosci kopca typu min
	int search(int val);					   //zwraca indeks elemntu o zadanym kluczu (numerze wierzcho³ka)
											   //wierzcho³ek ten bêdzie mieæ modyfikowany klucz 
											   //wiec potrzebny jest w³aœnie jego indeks w kolejce
	int searchEdge(int u, int v);			   //szuka w grafie danej krawêdzi
	void decreaseKey(int ver, int val);        //tutaj potrzebna jest dodatkowa funkcja do zmniejszenia klucza danego wierzcho³ka!!!
	bool isEmpty();							   //zwraca informacjê o tym, czy kolejka jest pusta: true jesli jest
	bool isInQueue(int v);					   //zwraca informacje czy dany wierzcho³ek jest w kolejce, jeœli jest, to true
	bool isEdgeInQueue(int u, int v);		   //zwraca iniformacjê o tym czy dana krawêdŸ NIESKIEROWANA ju¿ istnieje

	int Parent(int index);					   //zwraca indeks rodzica
	int leftSon(int index);					   //zwraca indeks lewego syna
	int rightSon(int index);				   //zwraca index prawego syna

	static const short int up = 1;             //przywracanie wlasnoci w górê
	static const short int down = -1;		   //przywracanie wlasnoci w dó³

	//pomocnicza funkcja kotrolna
	void printQueue();

	~Queue();
};

