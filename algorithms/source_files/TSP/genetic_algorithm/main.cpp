#pragma once
#include <iostream>
#include <conio.h>
#include <string.h>
#include "GeneticAlgorithmTSP.h"
#include "Timer.h"
using namespace std;

int main() {
	
	//MENU dla algorytmu SA

	bool testing = true;
	int decision = 0;
	string filename;
	int n;
	double n2;
	GeneticAlgorithmTSP *GA = new GeneticAlgorithmTSP();

	while (testing) {
		cout << "Problem komiwojazera --- Algorytm Genetyczny\n\n"
			"MENU\n"
			"Wczytaj graf z pliku --- 1\n"
			"Wyswietl ustawienia parametrow --- 2\n"
			"Ustaw kryterium czasowe stopu --- 3\n"
			"Ustaw liczbe iteracji --- 4\n"
			"Ustaw rozmiar populacji --- 5\n"
			"Ustaw liczbe osobnikow w turnieju --- 6\n"
			"Ustaw prawdopodobientwo krzyzowania --- 7\n"
			"Ustaw prawdopodobientwo mutacji --- 8\n"
			"Ustaw liczbe mutowanych genow --- 9\n"
			"Uruchom algorytm genetyczny --- 11\n"
			"Zakoncz --- 0\n"
			"Decyzja: ";
		cin >> decision;

		system("cls");

		switch (decision) {
		case 1:
			cout << "Podaj nazwe pliku: "; cin >> filename; cout << endl;
			GA->readGraphFromFile(filename);
			cout << "Wcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 2:
			GA->getParameters();
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 3:
			cout << "Podaj czas, jako calkowita liczbe sekund: ";
			cin >> n;
			if (n > 0) GA->setFinalTime(n);
			else cout << "Czas musi byc dodatni.\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 4:
			cout << "Podaj liczbe iteracji: ";
			cin >> n;
			if (n > 0) GA->setNumOfIterations(n);
			else cout << "Liczba musi byc dodatnia.\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 5:
			cout << "Podaj liczebnosc populacji (powinna byc parzysta): ";
			cin >> n;
			if (n > 0) GA->setSizeOfPopulation(n);
			else cout << "Liczebnosc musi byc dodatnia.\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 6:
			cout << "Podaj rozmiar turnieju: ";
			cin >> n;
			if (n > 0 && n<GA->getSizeOfPopulation()) GA->setNumOfKnights(n);
			else cout << "Rozmiar musi byc dodatni oraz nie moze przekraczac rozmiaru populacji.\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 7:
			cout << "Podaj prawdopodobienstwo krzyzowania: ";
			cin >> n2;
			if (n2 >= 0 && n2 <= 1.0) GA->setCrossoverProbability(n2);
			else cout << "Prawdopodobienstwo musi znadjowac sie w przedziale [0,1].\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 8:
			cout << "Podaj prawdopodobienstwo mutacji: ";
			cin >> n2;
			if (n2 >= 0 && n2 <= 1.0) GA->setMutationProbability(n2);
			else cout << "Prawdopodobienstwo musi znadjowac sie w przedziale [0,1].\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 9:
			cout << "Podaj liczbe mutowanych genow: ";
			cin >> n;
			if (n > 0) GA->setNumOfSwaps(n);
			else cout << "Liczba musi byc dodatnia.\n";
			cout << "\nWcisnij ENTER. (byc moze dwukrotnie)";
			_getch();
			_getch();
			system("cls");
			break;
		case 11:
			if (GA->graphExists()) {
				cout << "ALGORYTM GENETYCZNY\nDLA PROBLEMU KOMIWOJAZERA\n\n";
				GA->startGA();
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

	delete GA;

	system("cls");

	cout << "Aby wyjsc, wcisnij ENTER. (byc moze dwukrotnie)";
	_getch();
	_getch();

	return 0;
}