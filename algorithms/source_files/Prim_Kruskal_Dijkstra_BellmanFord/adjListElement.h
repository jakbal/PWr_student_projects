#pragma once
class adjListElement
{
public:
	adjListElement();
	adjListElement(int v, int w);

	int v; //wierzcho³ek s¹siedni
	int w; //waga krawêdzi
	adjListElement* next;

	//funkcja tworz¹ca nowy s¹siedni wierzcho³ek
	adjListElement* newVerticle(int v, int w);

	~adjListElement();
};

