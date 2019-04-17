#include "stdafx.h"
#include "treeSet.h"


treeSet::treeSet()
{
}


treeSet::treeSet(int x, int rank)
{
	this->x = x;
	this->rank = rank;
}

void treeSet::unionSet(treeSet **S, int y, int z)
{
	//y robi za x, z robi za y
	//krok1: operacji LINK
	int rootX = findSet(S, y);
	int rootY = findSet(S, z);
	if (S[rootX]->rank > S[rootY]->rank) {
		S[rootY]->x = rootX;
	}
	else {
		S[rootX]->x = rootY;
		if (S[rootX]->rank == S[rootY]->rank) {
			S[rootY]->rank += 1;
		}
	}

}


int treeSet::findSet(treeSet** S, int v)
{
	if (v != S[v]->x) {
		S[v]->x = findSet(S, S[v]->x);
	}
	return S[v]->x;
}

treeSet::~treeSet()
{
}
