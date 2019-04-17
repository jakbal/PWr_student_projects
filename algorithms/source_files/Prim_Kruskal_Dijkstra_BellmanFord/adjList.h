#pragma once
#include "adjListElement.h"
class adjList
{
public:
	adjList();

	adjListElement* head;

	void addEdge(int v, int w); //funkcja dodaje now¹ krawêdŸ do danej listy
	int searchWeight(int v);    //funkcja zwraca wagê danej krawêdzi

	~adjList();
};

