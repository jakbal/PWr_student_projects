#include "stdafx.h"
#include "Queue.h"
#include <iostream>


Queue::Queue(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	Q = new queueElement *[capacity];
	//wstêpna inicjalizacja kolejki
	for (int i = 0; i < capacity; i++) {
		Q[i] = nullptr;
	}
}

void Queue::insertNode(int v, int key)
{
	if (size == 0) {
		size++;
		queueElement* newQE = new queueElement(v, key);
		Q[size - 1] = newQE;
	}
	else {
		size++;
		queueElement* newQE = new queueElement(v, key);
		Q[size - 1] = newQE;			//wstaw nowy element na koniec kopca
		minHeapify(size - 1, this->up); //przywróæ w³ascnoœæ kopca typu min w gore
	}
}

void Queue::insertEdge(int u, int v, int key)
{
	if (size == 0) {
		size++;
		queueElement* newQE = new queueElement(u, v, key);
		Q[size - 1] = newQE;
		
	}
	else {
		size++;
		queueElement* newQE = new queueElement(u, v, key);
		Q[size - 1] = newQE;			//wstaw nowy element na koniec kopca
		minHeapify(size - 1, this->up); //przywróæ w³ascnoœæ kopca typu min w gore
		
	}
}

int Queue::extractRoot()
{
	int ver = -1;
	if (Q != nullptr && Q[0] != nullptr) {
										    //usuwaj korzen tylko je¿eli size>0
		if (size > 1) {
			ver = Q[0]->v;				//zapamietaj wierzcho³ek o najmniejszym kluczu
			Q[0]->v = Q[size - 1]->v;		//przenies ostatni wierzcho³ek na miejsce pierwszego
			Q[0]->key = Q[size - 1]->key;   //czyli przekopiuj numer wierzcho³ka i jego klucz
			delete Q[size - 1];				//usun ostatni (przed chwil¹) przekopiowany wierzcho³ek
			Q[size - 1] = nullptr;
			size--;					   //zmniejsz rozmiar
			minHeapify(0, this->down); //przywroc wlasnoc kopca typu min w dó³
		}							   //w przeciwnym razie size == 1 
		else if (size == 1) {
			ver = Q[0]->v;
			delete Q[0];
			Q[0] = nullptr;
			size--;
			delete[]Q;					//usuniêty zosta³ ostatni element kolejki, wiêc usuwamy tablicê Q
			Q = nullptr;				//i ustawiamy j¹ na nullptr
		}
	}else {
		std::cout << "\nKolejka jest pusta!\n";
	}
	
	return ver;
}

int* Queue::extractEdge()
{
	int* tab = new int[3];
	tab[0] = -1; tab[1] = -1; tab[2] = -1;

	if (Q != nullptr && Q[0] != nullptr) {
		//usuwaj korzen tylko je¿eli size>0
		if (size > 1) {
			tab[0] = Q[0]->u;				//zapamietaj dane krawedzi
			tab[1] = Q[0]->v;
			tab[2] = Q[0]->key;
			Q[0]->u = Q[size - 1]->u;
			Q[0]->v = Q[size - 1]->v;		//przenies ostatni wierzcho³ek na miejsce pierwszego
			Q[0]->key = Q[size - 1]->key;   //czyli przekopiuj numer wierzcho³ka i jego klucz
			delete Q[size - 1];				//usun ostatni (przed chwil¹) przekopiowany wierzcho³ek
			Q[size - 1] = nullptr;
			size--;					   //zmniejsz rozmiar
			minHeapify(0, this->down); //przywroc wlasnoc kopca typu min w dó³
		}							   //w przeciwnym razie size == 1 
		else if (size == 1) {
			tab[0] = Q[0]->u;
			tab[1] = Q[0]->v;
			tab[2] = Q[0]->key;
			delete Q[0];
			Q[0] = nullptr;
			delete[]Q;					//usuniêty zosta³ ostatni element kolejki, wiêc usuwamy tablicê Q
			Q = nullptr;				//i ustawiamy j¹ na nullptr
			size--;
		}
	}
	else {
		std::cout << "\nKolejka jest pusta!\n";
	}

	return tab;
}

void Queue::minHeapify(int index, int direction)
{
	if (direction == this->up) {
		int p = Parent(index);
		int smalest;
		if ((p >= 0) && (Q[p]->key > Q[index]->key)) {
			//jezeli rodzic istnieje i jego key jest wiêksze od key syna
			//smalest przechowuje indeks syna
			smalest = index;
		}
		else smalest = p;//jezeli rodzic jest jest mniejszy od syna to smalest przechowuje indeks rodzica
		if (smalest != p) {
			//je¿eli to syn jest mniejszy
			//wykonaj poni¿szy algorytm
			int temp_u = Q[smalest]->u;
			int temp_v = Q[smalest]->v;		//zapamietaj atrybuty klucza
			int temp_key = Q[smalest]->key;
			Q[index]->u = Q[p]->u;
			Q[index]->v = Q[p]->v;			//wiêksze idzie na dó³
			Q[index]->key = Q[p]->key;
			Q[p]->u = temp_u;
			Q[p]->v = temp_v;				//mniejsze idzie na górê
			Q[p]->key = temp_key;
			minHeapify(p, this->up);//idŸ dalej do góry z indeksem poprzedniego ojca
		}
	}
	else if (direction == this->down) {
		//index jest tu indeksem rodzica
		int l = leftSon(index);
		int r = rightSon(index);
		int smalest;
		if ((l < (this->size)) && (Q[l]->key < Q[index]->key)) {
			smalest = l;
		}
		else {
			smalest = index;
		}
		if ((r < (this->size)) && (Q[r]->key < Q[smalest]->key)) {
			smalest = r;
		}
		if (smalest != index) {
			int temp_u = Q[index]->u;
			int temp_v = Q[index]->v;		//zapamiêtaj atrybuty rodzica
			int temp_key = Q[index]->key;
			Q[index]->u = Q[smalest]->u;
			Q[index]->v = Q[smalest]->v;	//na miejsce rodzica wprowadz mniejsze atrybuty
			Q[index]->key = Q[smalest]->key;
			Q[smalest]->u = temp_u;
			Q[smalest]->v = temp_v;			//na miejsce poprzednio mniejszego wêz³a
			Q[smalest]->key = temp_key;		//wprowadz zapamiêtane atrybbuty rodzica
			minHeapify(smalest, this->down);//idz dalej w dó³, z wêz³em który poprzednio wiêkszy
		}
	}
}

int Queue::search(int val)
{
	for (int i = 0; i < size; i++) {
		if (Q[i]->v == val) {
			return i;
		}
	}

	return -1; //je¿eli w kolejce nie ma wierzcho³ka val to zwroc -1
}

int Queue::searchEdge(int u, int v)
{
	for (int i = 0; i < size; i++) {
		if ((Q[i]->u == u && Q[i]->v == v) || (Q[i]->u == v && Q[i]->v == u)) {
			return i;
		}
	}

	return -1; //je¿eli w kolejce nie ma wierzcho³ka val to zwroc -1
}

void Queue::decreaseKey(int ver, int val)
{
	int index = search(ver);			//znajdŸ idneks wierzcho³ka
	int previous_key = Q[index]->key;   //zapamietaj poprzedni klucz
	Q[index]->key = val;				//zmieñ klucz danego wierzcho³ka
	if (previous_key > val) {
		minHeapify(index, this->up);
	}
	else if (previous_key < val) {
		minHeapify(index, this->down);
	}
}

bool Queue::isEmpty()
{
	return size == 0;
}

bool Queue::isInQueue(int v)
{
	int index = search(v);
	return index != -1;
}

bool Queue::isEdgeInQueue(int u, int v)
{
	int index = searchEdge(u, v);
	return index != -1;
}

int Queue::Parent(int index)
{
	int parent = ((index + 1) / 2 - 1);
	return parent;
}

int Queue::leftSon(int index)
{
	int leftSon = (2 * index + 1);
	return leftSon;
}

int Queue::rightSon(int index)
{
	int rightSon = (2 * index + 2);
	return rightSon;
}


void Queue::printQueue()
{
	if (Q != nullptr && Q[0] != nullptr) {
		for (int i = 0; i < size; i++) {
			std::cout << Q[i]->key << ":" << Q[i]->v << " ";
		}
	}
	else
	{
		std::cout << "Q jest pusta";
	}
}

Queue::~Queue()
{
	//je¿eli kolejka nie zostanie opró¿niona ca³kowicie
	//size > 0 i Q != nullptr
	//to usuwamy pozosta³e w niej elementy
	//oraz tablicê je przechowuj¹ce
	if (Q != nullptr) {
		for (int i = 0; i < size; i++) {
			delete Q[i];
			Q[i] = nullptr;
		}
		delete []Q;
		Q = nullptr;
	}
}
