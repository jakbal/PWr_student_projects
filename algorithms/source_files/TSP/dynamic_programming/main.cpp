#include "tspDynamicProgramming.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

long long int read_QPC();

int main() {
	
	//sekcja pomiarów
	/*SEKCJA POMIARÓW
	//zmienne czasowe
	long long int frequency, start, elapsed, total;
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	total = 0;
	int temp = 0;
	int repeat = 5;

	tspDynamicProgramming* TSP = new tspDynamicProgramming();

	//pêtla testowa dla pomiarów
	for (int i = 0; i < repeat; i++) {
		TSP->generateGraph(4); //dla 23 jest MAX ze wzglêdu na dozwolone miejsce
		start = read_QPC();
		temp = TSP->countPath();
		elapsed = read_QPC() - start;
		total += elapsed;
	}

	total /= repeat;

	cout << "Time [s] = " << (float)total / frequency << endl;
	cout << "Time [ms] = " << (1000.0 * total) / frequency << endl;
	cout << "Time [us] = " << (1000000.0 * total) / frequency << endl << endl;

	delete TSP;

	_getch();
	_getch();
	return 0;
	*/

	//sekcja menu
	bool testing = true;
	int decision = 0;
	int N = 0;
	string filename;
	tspDynamicProgramming* TSP = new tspDynamicProgramming();

	while (testing) {
		cout <<"Problem komiwojazera --- Programowanie Dynamiczne\n\n"
			   "MENU\n"
			   "Wczytaj graf z pliku --- 1\n"
			   "Generuj graf --- 2\n"
			   "Oblicz TSP --- 3\n"
			   "Zakoncz --- 0\n"
			   "Decyzja: ";
		cin >> decision;

		system("cls");

		switch (decision) {
			case 1:
				cout << "Podaj nazwe pliku: "; cin >> filename; cout << endl;
				TSP->loadGraphFromFile(filename);
				cout << "Wcisnij ENTER";
				_getch();
				_getch();
				system("cls");
				break;
			case 2:
				cout << "Podaj liczbe miast: "; cin >> N; cout << endl;
				if (N>=2 && N<=23) {
					TSP->generateGraph(N);
					cout << "Wcisnij ENTER.";
				}
				else {
					cout << "N musi lezec w przedziale <2,23>\n";
					cout << "Wcisnij ENTER";
				}
				_getch();
				_getch();
				system("cls");
				break;
			case 3:
				if (TSP->graphExists()) {
					cout << "Dlugosc sciezki: " << TSP->countPath() << endl;
					cout << "Sciezka: "; TSP->displayPath();
					cout << "\nWcisnij ENTER.";
				}
				else {
					cout << "Graf jest pusty!\n Wcisnij ENTER.";
				}
				_getch();
				_getch();
				system("cls");
				break;
			case 0:
				testing = false;
				break;
			default:
				cout << "Nie ma takiej opcji. \nWcisnij ENTER.";
				_getch();
				_getch();
				system("cls");
				break;
		}
	}

	delete TSP;

	system("cls");

	cout << "Aby wyjsc, wcisnij ENTER.";
	_getch();
	_getch();

	return 0;
}

long long int read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return((long long int)count.QuadPart);
}