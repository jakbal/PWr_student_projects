#include "stdafx.h"
#include "adjListElement.h"


adjListElement::adjListElement()
{
}

adjListElement::adjListElement(int v, int w)
{
	this->v = v;
	this->w = w;
	this->next = nullptr;
}


adjListElement * adjListElement::newVerticle(int v, int w)
{
	adjListElement *newV = new adjListElement(v, w);
	return newV;
}

adjListElement::~adjListElement()
{
}
