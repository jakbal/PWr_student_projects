#include "stdafx.h"
#include "adjList.h"


adjList::adjList()
{
	this->head = nullptr;
}


void adjList::addEdge(int v, int w)
{
	adjListElement* V = head->newVerticle(v, w);

	if (head == nullptr) {
		head = V;
	}
	else
	{
		V->next = head;
		head = V;
	}
}

int adjList::searchWeight(int v)
{
	int weight = 0;
	adjListElement* tempLE = head;
	while (tempLE != nullptr) {
		if (tempLE->v == v) {
			weight = tempLE->w;
			return weight;
		}
		tempLE = tempLE->next;
	}
	return weight;
}



adjList::~adjList()
{
}
