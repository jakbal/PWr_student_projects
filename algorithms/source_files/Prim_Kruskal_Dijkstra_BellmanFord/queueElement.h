#pragma once
class queueElement
{
public:
	queueElement(int v, int key);
	queueElement(int u, int v, int key);
	int u;   //src vertex - wierzchołek startowy
	int v;   //dest vertex - wierzchołek końcowy
	int key; //klucz
	~queueElement();
};

