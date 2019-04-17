#pragma once
class treeSet
{
public:
	treeSet();
	treeSet(int x, int rank); //operacja MAKE-SET

	int x;
	int rank;

	void unionSet(treeSet **S, int y, int z);
	int findSet(treeSet** S, int v);

	~treeSet();
};

