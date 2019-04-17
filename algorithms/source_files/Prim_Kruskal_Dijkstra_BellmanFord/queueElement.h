#pragma once
class queueElement
{
public:
	queueElement(int v, int key);
	queueElement(int u, int v, int key);
	int u;   //src vertex - wierzcho³ek startowy
	int v;   //dest vertex - wierzcho³ek koñcowy
	int key; //klucz
	~queueElement();
};

