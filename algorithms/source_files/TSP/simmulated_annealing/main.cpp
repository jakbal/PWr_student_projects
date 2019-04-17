#include <iostream>
#include <conio.h>
#include <string.h>
#include "SimmulatedAnnealingTSP.h"
#include "Timer.h"
using namespace std;

int main() {
	//MENU dla algorytmu SA

	bool testing = true;
	int decision = 0;
	string filename;
	SimmulatedAnnealingTSP *SA = new SimmulatedAnnealingTSP();

	while (testing) {
		cout << "Problem komiwojazera --- Symulowane Wyzarzanie\n\n"
			"MENU\n"
			"Wczytaj graf z pliku --- 1\n"
			"Wybierz typ sasiedztwa --- 2\n"
			"Ustaw parametry --- 3\n"
			"Symulowane wyzarzanie --- 4\n"
			"Zakoncz --- 0\n"
			"Decyzja: ";
		cin >> decision;

		system("cls");

		switch (decision) {
		case 1:
			cout << "Podaj nazwe pliku: "; cin >> filename; cout << endl;
			SA->readGraphFromFile(filename);
			cout << "Wcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 2:
			SA->setNeighbourhood();
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 3:
			SA->setParameters();
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 4:
			if (SA->graphExists()) {
				cout << "ALGORYTM SYMULOWANEGO WYZARZANIA\nDLA PROBLEMU KOMIWOJAZERA\n\nWyniki:\n\n";
				SA->simmulateAnneal();
				cout << "\n-> ostatnie rozwiazanie: " << SA->getCurrentRoute() << endl;
				cout << "-> najlepsze rozwiazanie: " << SA->getBestRoute() << endl;
			}
			else {
				cout << "Graf jest pusty.\nWpierw wczytaj go z pliku.\n";
			}
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 0:
			testing = false;
			break;
		default:
			cout << "Nie ma takiej opcji. \nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		}
	}

	delete SA;

	system("cls");

	cout << "Aby wyjsc, wcisnij ENTER. (byc moze dwukrotnie)";
	_getch();
	_getch();

	return 0;
}