#include "stdafx.h"
#include "queueElement.h"


queueElement::queueElement(int v, int key)
{
	this->u = 0;
	this->v = v;
	this->key = key;
}

queueElement::queueElement(int u, int v, int key)
{
	this->u = u;		//wierzcho³ek pocz¹tkowy
	this->v = v;		//wierzcho³ek koñcowy
	this->key = key;    //kluczem jest waga krawêdzi
}


queueElement::~queueElement()
{
}
