#include "stdafx.h"
#include "Graph.h"
#include <limits>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "treeSet.h"
#include <random>


Graph::Graph()
{

	this->V = 0;
	this->E = 0;
	this->firstV = -1;
	this->lastV = -1;
}

void Graph::primMatrix(int root)
{
	if (root<V && root>=0 && adjMatrix != nullptr)
	{
		int *parent = new int[V]; //tablica poprzednikow
		int *keys = new int[V];   //klucze dla wierzcho³ków, inicjalizowane INFINITY
		bool *mst = new bool[V];  //tablica przechowuj¹ca informacjê, czy dany wierzcho³ek wszed³ do MST

		//inicjalizacja kluczy oraz mst
		for (int i = 0; i < V; i++) {
			keys[i] = INF;
			mst[i] = false;
			parent[i] = -1; //inicjujemy poprzedników wszystkich wierzcho³ków
							//wartoœci¹ NIL = -1
		}

		//inicjalizacja korzenia
		keys[root] = 0;
		parent[root] = -1; //wierzcho³ek pocz¹tkowy staje siê korzeniem drzewa 

		//poniewa¿ korzeñ ju¿ jest w drzewie wykonamy V-1 opeeracji
		//oraz poniewa¿ do ostatniego pozosta³ego wierzcho³ka nale¿y rozwa¿yæ ju¿ tylko krawêdzie z nim incydentne
		for (int i = 0; i < V-1; i++) {

			int v = minKey(mst, keys); //znajdz wierzho³ek o minimalnym kluczu, który nie nale¿y jeszcze do MST
			if (v != -1) {
				mst[v] = true;			   //oznacz wierzcho³ek jako nale¿¹cy do MST

				//aktulizuj poprzednika oraz klucz (wagê krawêdzi) dla danego wierzcho³ka
				//wierzcho³ek ten nie mo¿e znjadowaæ siê jeszcze w MST
				for (int u = 0; u < V; u++) {
					//1. jezeli istnieje krawedz
					//2. jezeli wierzcho³ek nie nale¿y do MST
					//3. je¿eli waga danej krawedzi jest mniejsza od klucza danego wierzcho³ka
					if (adjMatrix[v][u] && (mst[u] == false) && (adjMatrix[v][u] < keys[u])) {
						parent[u] = v;
						keys[u] = adjMatrix[v][u];
					}
				}
			}
		}
		//na czas testów trzeba zakomentowaæ wyœwietlanie wyników
		printMSTMatrix(parent);
		//cout << "OK\n";
		
		delete[]parent;
		delete[]keys;
		delete[]mst;
	}
	else
	{
		cout << "\nPodany wierzholek lub graf nie istnieje.\n";
	}
}

void Graph::primList(int root)
{
	if (root<V && root >= 0 && adjMatrix != nullptr) {
		int *parent = new int[V];
		int *keys = new int[V];
		bool *mst = new bool[V];
		Queue* Q = new Queue(V);

		for (int i = 0; i < V; i++) {
			parent[i] = -1;
			keys[i] = INF;
			mst[i] = false;
		}

		//klucz korzenia jest 0, to gwarantuje mu bycie pierwszym w kolejce
		keys[root] = 0;

		//do kolejki ³adowane s¹ wszytskie wierzcho³ki
		//kluczem s¹ wartoœci z keys
		for (int i = 0; i < V; i++) {
			Q->insertNode(i, keys[i]);
		}

		while (!(Q->isEmpty())) {
			int u = Q->extractRoot();				//wyci¹gamy z kolejki wierzcho³ek o najmniejszym kluczu
			mst[u] = true;							//wierzcho³ek ten dok³admy do drzewa MST

			adjListElement* tempLE = list[u].head;  //lista krawêdzi incydentnych z u
			while (tempLE != nullptr) {

				if (mst[tempLE->v] == false && Q->isInQueue(tempLE->v) && tempLE->w < keys[tempLE->v]) {
					keys[tempLE->v] = tempLE->w;
					parent[tempLE->v] = u;
					Q->decreaseKey(tempLE->v, keys[tempLE->v]);
				}

				tempLE = tempLE->next;
			}
		}

		printMSTList(parent);
		//cout << "OK\n";
		delete[]parent;
		delete[]keys;
		delete[]mst;
		delete Q;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::kruskalMatrix(int root)
{
	if (root >= 0 && root < V&& adjMatrix != nullptr) {
		queueElement** results = new queueElement *[V];//tablica obiektów queueElement, gdzie ka¿dy obiekt reprezentuje krawêdŸ
		Queue* Q = new Queue(E); //kolejka ktorwa bêdzie mieæ krawêdzie posortowane na podstawie ich wagi
		treeSet** S = new treeSet *[V]; //tablica zbiorów roz³¹cznych
		int* tab = nullptr; //tablica przechowuj¹ca atrybuty aktualnie przetwarzanej krawêdzi - (u,v,w)
		int edges = 0;

		//inicjalizacja drzew jednowierzcho³kowych
		for (int i = 0; i < V; i++) {
			S[i] = new treeSet(i, 0);
		}

		//Macierz jest symetryczna
		for (int i = 0; i < V; i++) {
			for (int k = i + 1; k < V; k++) {
				if (adjMatrix[i][k]) {
					Q->insertEdge(i, k, adjMatrix[i][k]); //dodaj krawedŸ do kolejki je¿eli istnieje {!= 0}
				}
			}
		}

		//Q jest kolejk¹ priorytetow¹ realizowan¹ jako kopiec typu min
		//zatem wszystkie krawêdzie znajduj¹ce siê w niej s¹ ju¿ w kolejnoœci niemalej¹cej

		while (!Q->isEmpty()) {
			tab = Q->extractEdge();

			if (S[0]->findSet(S, tab[0]) != S[0]->findSet(S, tab[1])) {
				results[edges] = new queueElement(tab[0], tab[1], tab[2]);
				edges++;
				S[0]->unionSet(S, tab[0], tab[1]);
			}

			delete[]tab;	//nale¿y pamiêtaæ o usuniêcie tab
			tab = nullptr;	//poniewa¿ w Queue jest generowana tablica 3-el. operatorem new
							//jezeli jej tu nie usuniemy to na koñcu usunêlibysmy tylko ostatni obiekt
							//a wszystkie XXX taabel pozosta³oby niezwolnionych
		}

		printMST(results, edges);
		//cout << "OK\n";
		//usuwanie obiektów
		for (int i = 0; i < V; i++) {
			delete S[i];
		}
		delete[]S;

		for (int i = 0; i < edges; i++) {

			delete results[i];
		}
		delete[]results;

		delete Q;

		//algorytm powinien wyci¹gn¹æ z kolejki wszytskie mo¿liwe krawêdzie
		//a wczeœniejsza pêtla powinna usun¹æ wszystkie wygenerowane tab
		//gdyby jendak tab by³ inny ni¿ nullptr to nale¿y go usun¹æ/zwolniæ
		if (tab != nullptr)
			delete[]tab;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::kruskalList(int root)
{
	if (root >= 0 && root < V&& adjMatrix != nullptr) {
		queueElement** results = new queueElement *[V];//tablica obiektów queueElement, gdzie ka¿dy obiekt reprezentuje krawêdŸ
		Queue* Q = new Queue(E); //kolejka ktorwa bêdzie mieæ krawêdzie posortowane na podstawie ich wagi
		treeSet** S = new treeSet *[V]; //tablica zbiorów roz³¹cznych
		int* tab = nullptr; //tablica przechowuj¹ca atrybuty aktualnie przetwarzanej krawêdzi
		int edges = 0;

		//inicjalizacja drzew jednowierzcho³kowych
		for (int i = 0; i < V; i++) {
			S[i] = new treeSet(i, 0);
		}

		for (int i = 0; i < V; i++) {
			adjListElement* tempLE = list[i].head;

			while (tempLE != nullptr) {

				if (!(Q->isEdgeInQueue(i, tempLE->v))) {
					Q->insertEdge(i, tempLE->v, tempLE->w);
				}

				tempLE = tempLE->next;
			}
		}

		//Q jest kolejk¹ priorytetow¹ realizowan¹ jako kopiec typu min
		//zatem wszystkie krawêdzie znajduj¹ce siê w niej s¹ ju¿ w kolejnoœci niemalej¹cej

		while (!Q->isEmpty()) {
			tab = Q->extractEdge();

			if (S[0]->findSet(S, tab[0]) != S[0]->findSet(S, tab[1])) {
				results[edges] = new queueElement(tab[0], tab[1], tab[2]);
				edges++;
				S[0]->unionSet(S, tab[0], tab[1]);
			}

			delete[]tab;
			tab = nullptr;
		}

		printMST(results, edges);
		//cout << "OK\n";
		//usuwanie obiektów
		for (int i = 0; i < V; i++) {
			delete S[i];
		}
		delete[]S;

		for (int i = 0; i < edges; i++) {

			delete results[i];
		}
		delete[]results;

		delete Q;

		if (tab != nullptr)
			delete[]tab;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::dijkstraMatrix(int s)
{
	if (s >= -1 && s < V && adjMatrix != nullptr) {
		//je¿eli wywo³amay algorytm dla minmalnej sciezki
		//z arg domyœlnym, oznacza to, ¿e chcemy wywo³aæ go z wierzcho³kiem
		//oznaczonym jako firstV
		if (s == -1)
			s = firstV;

		int *parent = new int[V];
		int *distance = new int[V];
		bool *Set = new bool[V];

		//procedura INITIALIZE-SINGLE-SOURCE
		for (int i = 0; i < V; i++) {
			parent[i] = -1;
			distance[i] = INT_MAX;
			Set[i] = false;
		}
		distance[s] = 0;
		//koniec procedury

		//g³ówna pêtla
		for (int i = 0; i < V - 1; i++) {
			int u = minDis(distance, Set);  //wyjmij najmniejszy element
			Set[u] = true;					//do³¹cz go do zbioru

			//pêtla z procedur¹ relaksacji ka¿dej incydentej
			//krawêdzi wzglêdem wierzcho³ka wybranego wierzcho³ka u

			//opis poni¿szego warunku znajduje siê w algorytmie Dijkstry dla listy
			//poni¿szy warunek nie jest tu niezbêdny na pierwszy rzut oka
			//jednak¿e wynika to ze sposobu generacji grafu
			//je¿eli graf by³by generowany inaczej, wyst¹pi³by ten sam b³¹d co w przypadku reprezentacji listowej
			//funkcja minDis zwraca wierzcho³ek o dystansie najmniejszym, w pewnym momenice zaczê³aby zwracaæ INT_MAX
			//Ale poniewa¿ zwraca w kolejnoœci od najwy¿szego do najmniejszego wierzcho³ka czyli (dla v=5) 3,2,1,0
			//a graf zapewnia po³¹czenia id¹c po kolei od 0->1->2 i tak dalej, wobec tego nigdy nie bêdzie istnieæ po³¹czenie wierzcho³ka o
			//indeksie wiêkszym z indeksem mniejszym, wiêc wewnêtrzny warunek if nie jest spe³niony bo adjM[3][0,1,2] nie istnieje
			//d³ugie wyt³umaczenie, ale prawdziwe, s³ownie wyt³umaczyæ by³oby ³atwiej
			if (distance[u] != INT_MAX) {
				for (int j = 0; j < V; j++) {
					//procedura RELAX
					if (Set[j] == false && adjMatrix[u][j] && distance[j] > (distance[u] + adjMatrix[u][j])) {
						distance[j] = distance[u] + adjMatrix[u][j];
						parent[j] = u;
					}
					//koniec procedury
				}
			}
		}
		//koniec g³ównej pêtli

		printSP(parent, distance, s);
		//cout << "SUKCES DIJ_M\n";
		delete[]parent;
		delete[]distance;
		delete[]Set;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::dijkstraList(int s)
{
	if (s >= -1 && s < V && adjMatrix != nullptr) {
		if (s == -1)
			s = firstV;

		int *parent = new int[V];
		int *distance = new int[V];
		bool *Set = new bool[V];
		Queue *Q = new Queue(V);

		//procedura INITIALIZE-SINGLE-SOURCE
		for (int i = 0; i < V; i++) {
			parent[i] = -1;
			distance[i] = INT_MAX;
			Set[i] = false;
		}
		distance[s] = 0;
		//koniec procedury

		//za³adowanie do kolejki wszystki wierzcho³ków
		//kluczem s¹ distance[i]
		for (int i = 0; i < V; i++) {
			Q->insertNode(i, distance[i]);
		}

		//g³ówna pêtla
		while (!Q->isEmpty()) {
			int u = Q->extractRoot();
			Set[u] = true;
			//podczas opró¿niania kolejki Q klucze osi¹galnych wierzcho³ków s¹ modyfikowane
			//jednak¿e istnieje szansa, ¿e pewne wierzcho³ki s¹ nieosi¹glane
			//ale Q oprónia¿my do koñca, wiêc wyst¹pi sytuacja, ¿e przetwarzamy wierzcho³ki nieosi¹glane z danego
			//doprwoadzi to do przekrêcenia siê licznika i otrzymyawania nieprawdziwych wyników
			//zabezpieczenie przed tak¹ sytuacj¹ stanowi dodatkowy warunek w poni¿szym if(...)
			//który sprawdzi czy wyci¹gniêty wierzcho³ek w jakiklowiek sposób by³ wczesniej osi¹galny
			//je¿eli nie by³, oznacza, to ¿e nigdy nie bêdzie i nie ma potrzeby rozwa¿ania jego s¹siadów
			if (distance[u] != INT_MAX) {
				adjListElement *tempLE = list[u].head;
				while (tempLE != nullptr) {

					//na ka¿dym wierzcho³ku wykonujemy procedurê relaksacji
					//zawsze brany jest wierzcho³ek - 'u' o kluczu minimalnym 
					//którego dist[u] nie jest ju¿ równe INT_MAX
					//z tego wzglêdu nie nastêpuje "przekrêcenie licznika"
					if (Set[tempLE->v] == false && distance[tempLE->v] > (distance[u] + tempLE->w)) {
						distance[tempLE->v] = distance[u] + tempLE->w;
						Q->decreaseKey(tempLE->v, distance[tempLE->v]);
						parent[tempLE->v] = u;
					}

					tempLE = tempLE->next;
				}
			}
		}
		//koniec pêtli

		printSP(parent, distance, s);
		//cout << "SUKCES DIJ_L\n";
		delete[]parent;
		delete[]distance;
		delete[]Set;
		delete Q;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::bellmanfordMatrix(int s)
{
	if (s >= -1 && s < V && adjMatrix != nullptr) {
		if (s == -1)
			s = firstV;

		int *parent = new int[V];
		int *distance = new int[V];
		bool negativeCycle = false;

		//procedura INITIALIZE-SINGLE-SOURCE
		for (int i = 0; i < V; i++) {
			parent[i] = -1;
			distance[i] = INF;
		}
		distance[s] = 0;
		//koniec procedury

		//pêtla 1
		for (int k = 0; k < V - 1; k++) {
			//dla ka¿dej krawêdzi w grafie wykonaj procedurê RELAX
			for (int i = 0; i < V; i++) {
				//warunek if analogiczny jak dla alg Dij
				//pozwala na u¿ywanie wartoœci INF
				if (distance[i] != INF) {
					for (int j = 0; j < V; j++) {
						if (adjMatrix[i][j] && distance[j] > (distance[i] + adjMatrix[i][j])) {
							distance[j] = distance[i] + adjMatrix[i][j];
							parent[j] = i;
						}
					}
				}
			}

		}
		//koniec pêtli 1

		//pêtla 2 POPRAWKA!!!!!!!
		//sprawdza czy graf ma cykle ujemne
		for (int i = 0; i < V; i++) {
			//warunek if analogiczny jak dla alg Dij
			//pozwala to na u¿ywanie wartoœci INT_MAX
			if (distance[i] != INF) {
				for (int j = 0; j < V; j++) {
					if (adjMatrix[i][j] && distance[j] > (distance[i] + adjMatrix[i][j])) {
						negativeCycle = true;
					}
				}
			}
		}
		//koniec pêtli 2

		/*for (int i = 0; i < V; i++) {
			cout << distance[i] << endl;
		}*/

		if (!negativeCycle) {
			printSP(parent, distance, s);
			//cout << "SUKCES BF_M\n";
		}
		else {
			cout << "\nIstnieje negatywny cykl.\n";
		}

		delete[]parent;
		delete[]distance;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::bellmanfordList(int s)
{
	if (s >= -1 && s < V && adjMatrix != nullptr) {
		if (s == -1)
			s = firstV;

		int *parent = new int[V];
		int *distance = new int[V];
		bool negativeCycle = false;

		//procedura INITIALIZE-SINGLE-SOURCE
		for (int i = 0; i < V; i++) {
			parent[i] = -1;
			//UWAGA zosta³a zamieszcozna przy bellmanfordMatrix!
			distance[i] = INF;
		}
		distance[s] = 0;
		//koniec procedury

		adjListElement *tempLE;
		//pêtla 1
		for (int k = 0; k < V - 1; k++) {
			//V-1 razy
			//dla ka¿dej krawêdzi w grafie wykonaj procedurê RELAX
			for (int i = 0; i < V; i++) {
				//warunek if analogiczny jak dla alg Dij
				//pozwala to na u¿ywanie wartoœci INT_MAX
				if (distance[i] != INF) {
					tempLE = list[i].head;

					while (tempLE != nullptr) {
						if (distance[tempLE->v] > (distance[i] + tempLE->w)) {
							distance[tempLE->v] = distance[i] + tempLE->w;
							parent[tempLE->v] = i;
						}

						tempLE = tempLE->next;
					}
				}
			}
		}
		//koniec pêtli 1

		//pêtla 2
		//sprawdza czy graf ma cykle negatywne
		for (int i = 0; i < V; i++) {
			if (distance[i] != INF) {
				tempLE = list[i].head;
				//warunek if analogiczny jak dla alg Dij
				//pozwala to na u¿ywanie wartoœci INT_MAX
				while (tempLE != nullptr) {
					if (distance[tempLE->v] > (distance[i] + tempLE->w)) {
						distance[tempLE->v] = distance[i] + tempLE->w;
						parent[tempLE->v] = i;
					}

					tempLE = tempLE->next;
				}
			}
		}
		//koniec pêtli 2

		if (!negativeCycle) {
			printSP(parent, distance, s);
			//cout << "BFL";
		}
		else {
			cout << "\nIstnieje negatywny cykl.\n";
		}

		delete[]parent;
		delete[]distance;
	}
	else {
		cout << "\nPodany wierzcholek lub graf nie istnieje!\n";
	}
}

void Graph::printMSTMatrix(int *parent)
{
	long long int weightMST = 0;
	cout << "\nMST(Prim_adjMatrix)\nEDGE (v1,v2) --- WEIGHT\n\n";
	for (int i = 0; i < V; i++) {
		if (parent[i] != -1) {
			cout << "(" << i << ", " << parent[i] << ") --- " << adjMatrix[i][parent[i]] << "\n";
			weightMST += adjMatrix[i][parent[i]];
		}
	}
	cout << "\nWaga MST: " << weightMST << endl;
}

void Graph::printMSTList(int *parent)
{
	long long int weightMST = 0;
	int tempWeight = 0;
	cout << "\nMST(Prim_adjList)\nEDGE (v1,v2) --- WEIGHT\n\n";
	for (int i = 0; i < V; i++) {
		if (parent[i] != -1) {
			tempWeight = list[i].searchWeight(parent[i]);
			cout << "(" << i << ", " << parent[i] << ") --- " << tempWeight << "\n";
			weightMST += tempWeight;
		}
	}
	cout << "\nWaga MST: " << weightMST << endl;
}

void Graph::printMST(queueElement ** MST, int e)
{
	long long int weightMST = 0;
	cout << "\nMST(Kruskal)\nEDGE (v1,v2) --- WEIGHT\n\n";
	for (int i = 0; i < e; i++) {
		cout << "(" << MST[i]->u << ", " << MST[i]->v << ") --- " << MST[i]->key << "\n";
		weightMST += MST[i]->key; //dodaj wage po³¹czenia
	}
	cout << "\nWaga MST: " << weightMST << endl;
}

void Graph::printSP(int * parent, int *distance, int s)
{
	cout << "Start: " << s << endl;
	cout << "Koniec | Dystans | Sciezka\n";
	for (int i = 0; i < V; i++) {
		
		if (distance[i] != INT_MAX && distance[i] != INF_BF) {
			cout << i << " | " << distance[i] << " | ";
			printPath(parent, s, i);
			cout << endl;
		}
		else {
			cout << i << " | " << " * " << " | ";
			printPath(parent, s, i);
			cout << endl;
		}

	}
}

void Graph::printPath(int * parent, int s, int v)
{
	if (v == s) {
		cout << s << " ";
	}
	else if (parent[v] == -1) {
		cout << "Brak sciezki. ";
	}
	else
	{
		printPath(parent, s, parent[v]);
		cout << v << " ";
	}
}

//funkcja dla algorytmu Prima w zapisie macierzowym
//jej zadaniem jest odnalezienie wierzcho³ka 
//o minimalnym kluczu, który nie zosta³ jeszcze zawarty
//w zbiorze wierzcho³ków drzewa MST
int Graph::minKey(bool * mst, int * keys)
{
	int INF = this->INF;
	int index = -1;
	for (int i = 0; i < V; i++) {
		if (keys[i] < INF && mst[i] == false) {
			INF = keys[i];
			index = i;
		}
	}
	return index;
}

int Graph::minDis(int * distance, bool * Set)
{
	int min = INF;
	int index;

	for (int i = 0; i < V; i++) {
		if (Set[i] == false && distance[i] <= min) {
			min = distance[i];
			index = i;
		}
	}

	return index;

}

void Graph::createEmptyAdjMatrix()
{
	if (adjMatrix == nullptr) {
					
		if (V > 0) {
			adjMatrix = new int *[V];		//utworzenie wierszy
			for (int i = 0; i < V; i++) {
				adjMatrix[i] = new int[V];	//utworzenie kolumn
			}

			//inicajlizacja macierzy
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					adjMatrix[i][j] = 0;
				}
			}
		}
		else {
			cout << "\nLiczba wierzcho³ków musi byæ dodatnia!\n";
		}
	}
	else {
		cout << "\nMacierz juz istnieje.\n";
	}
}

void Graph::createList()
{
	if (adjMatrix != nullptr) {
		list = new adjList[V];
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (adjMatrix[i][j] != 0) {
					list[i].addEdge(j, adjMatrix[i][j]);
				}
			}
		}
	}
	else {
		cout << "\nMacierz jest pusta.\n";
	}
}

void Graph::generateUndirectedGraph(int v, int d)
{

	if (v > 0 && d >= 0 && d <= 100) {
		clearGraph();
		this->V = v;
		int e = (d*(v*(v - 1))) / 200;	//za ka¿dym razem bêdzie brana pod³oga z obliczonej wartoœci
		this->E = e;
		this->firstV = 0;
		this->lastV = 0;
		createEmptyAdjMatrix();			//utwórz pust¹ macierz s¹siedztwa wype³nion¹ zerami

		if (V != 1) {
			int w = 0;										//w przechowuje wylosowan¹ wagê dla danej krawêdzi
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> dist(1, 100000);	//przedzia³ nie mo¿e byæ za du¿y, ¿eby podczas pomiarów nie nast¹pi³o przekrêcenie licnzika w tablicach distance które s¹ int, a INT_MAX to ponad 2 milairdy
			//przyjêta zosta³a nastêpuj¹ca taktyka
			//zapewniaj¹ca, ¿e w wygenerowanym grafie, bêdzie istnieæ
			//minimalne drzewo rozpinaj¹ce
			//polega ona na po³¹czeniu wszytskich wierzcho³ków z wierzcho³kiem zerowym
			//a nastêpnie pseudolosowym dodaniu pozosta³ej liczby krawêdzi
			//KROK 1
			
			for (int j = 1, i=0; j < V; j++) {
				if (e > 0) {
					w = dist(gen);
					adjMatrix[i][j] = w;	//macierz grafu nieskierowanego
					adjMatrix[j][i] = w;	//jest symetryczna
					e--;					//dodano krawêdŸ, wiêc pula zostaje zmniejszona o jeden
				}
			}
			//KROK2
			//powtarzaj pêtlê dopóki wszystkie krawêdzie
			//nie zostan¹ wykorzystane
			int i = 0, j = 0;
			while (e > 0) {

				i = rand() % V;
				j = rand() % V;
				//i i j identyfikuj¹ dwa wierzcho³ki zatem
				//i i j musz¹ byæ ró¿ne (inaczej pêtla)
				//pula krawêdzi nie mo¿e byæ zerowa - warunek tu ju¿ chyba niekonieczny
				//pomiêdzy wierzcho³kami nie mo¿e jeszcze istnieæ krawêdŸ
				if (i != j && e > 0 && (adjMatrix[i][j] == 0)) {
					w = dist(gen);
					adjMatrix[i][j] = w;
					adjMatrix[j][i] = w;
					e--;
				}
			}
		}
		//je¿eli V == 1 to znaczy, ¿e istnieje tylko jeden wierzcho³ek
		//gdyby daæ krawêdŸ powsta³by cykl

		createList(); //po utworzeniu macierzy na jej podstawie mo¿na utworzyæ reprezentacjê listow¹
	}
	else {
		cout << "\nIlosc wierzcholkow musi byc dodatnia a gestosc nalezec do przedzialu [0,100].\n";
	}
}

void Graph::generateDirectedGraph(int v, int d)
{

	if (v > 0 && d >= 0 && d <= 100) {
		clearGraph();
		this->V = v;
		int e = (d*(v*v)) / 100;
		this->E = e;
		this->firstV = 0;
		this->lastV = 0;
		createEmptyAdjMatrix();

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1, 100000); //przedzia³ do 100 000

		//Krok 1
		//utworzenie cyklu, aby ka¿dy wierzcho³ek by³ osi¹galny z dowolnego wierzcho³ka
		for (int i = 0, j = 1; i < V; i++, j++) {
			if (e > 0) {

				if (j == V) {
					//zapewnienie cyklu
					//ostatni wierzcho³ek i = V-1 musi byæ po³¹czony z pierwszym j = 0
					j = 0;
				}

				adjMatrix[i][j] = dist(gen);
				e--;
			}
		}

		//KROK 2
		//rozdysponowanie pozosta³ymi krawêdziami
		int i = 0, j = 0;
		while (e > 0) {
			i = rand() % V;
			j = rand() % V;
			//i i j identyfikuj¹ dwa wierzcho³ki
			//pula krawêdzi nie mo¿e byæ zerowa - warunek tu ju¿ chyba niekonieczny
			//pomiêdzy wierzcho³kami nie mo¿e jeszcze istnieæ krawêdŸ
			if (e > 0 && (adjMatrix[i][j] == 0)) {
				adjMatrix[i][j] = dist(gen);
				e--;
			}
		}
		createList(); 
	}
	else {
		cout << "\nIlosc wierzcholkow musi byc dodatnia a gestosc nalezec do przedzialu [0,100].\n";
	}
}

void Graph::readUndirectedGraphFromFile(string filename)
{
	clearGraph(); //je¿eli graf istnieje to go usun

	ifstream file;
	int tab[4];
	file.open(filename.c_str());
	
	if (file.is_open()) {

		if (readLine(file, tab, 4)) {
			//wczytanie i inicjalzacja podstawowych danych
			E = tab[0];
			V = tab[1];
			if (tab[2] >= 0 && tab[2] < V)
				firstV = tab[2];
			else
				firstV = 0;
			lastV = tab[3];

			createEmptyAdjMatrix();

			for (int i = 0; i < E; i++) {
				if(readLine(file,tab,3)){
					adjMatrix[tab[0]][tab[1]] = tab[2];
					adjMatrix[tab[1]][tab[0]] = tab[2];
				}
				else{
					cout << "\nFILE ERROR - EDGE\n";
				}
			}

			//macierz zosta³a utworzona
			//mo¿na zatem wygenerowaæ listê
			createList();

		}
		else {
			cout << "\nFILE ERROR - INFO\n";
		}

		file.close();

	}
	else {
		cout << "\nFILE ERROR - OPEN\n";
	}

}

void Graph::readDirectedGraphFromFile(string filename)
{
	clearGraph(); //je¿eli graf istnieje to go usun

	ifstream file;
	int tab[4];
	file.open(filename.c_str());

	if (file.is_open()) {

		if (readLine(file, tab, 4)) {
			//wczytanie i inicjalzacja podstawowych danych
			E = tab[0];
			V = tab[1];
			if (tab[2] >= 0 && tab[2] < V)
				firstV = tab[2];
			else
				firstV = 0;
			lastV = tab[3];

			createEmptyAdjMatrix();

			for (int i = 0; i < E; i++) {
				if (readLine(file, tab, 3)) {
					adjMatrix[tab[0]][tab[1]] = tab[2];
				}
				else {
					cout << "\nFILE ERROR - EDGE\n";
				}
			}

			//macierz zosta³a utworzona
			//mo¿na zatem wygenerowaæ listê
			createList();

		}
		else {
			cout << "\nFILE ERROR - INFO\n";
		}

		file.close();

	}
	else {
		cout << "\nFILE ERROR - OPEN\n";
	}

}

bool Graph::readLine(ifstream & file, int tab[], int size)
{
	string s;
	getline(file, s);
	if (file.fail() || s.empty())
		return false;
	istringstream in_ss(s);
	for (int i = 0; i < size; i++) {
		in_ss >> tab[i];
		if (in_ss.fail())
			return false;
	}
	return true;
}

void Graph::printAdjMatrix()
{
	if (adjMatrix != nullptr) {
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				cout << adjMatrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "\nGraf nie istnieje. Macierz jest pusta.\n";
	}
}

void Graph::printAdjList()
{
	if (list != nullptr) {
		adjListElement* ver = nullptr;
		for (int i = 0; i < V; i++) {
			ver = list[i].head;
			cout << i;
			while (ver != nullptr) {
				cout << " ... " << ver->v << ":" << ver->w;
				ver = ver->next;
			}
			cout << endl;
		}
	}
	else {
		cout << "\nGraf nie istnieje. Lista jest pusta.\n";
	}
}

void Graph::clearGraph()
{
	//usuniecie macierzy sasiedztwa
	if (adjMatrix != nullptr) {
		for (int i = 0; i < V; i++) {
			delete [] adjMatrix[i];
		}
		delete [] adjMatrix;
		adjMatrix = nullptr;
		//cout << "\nMacierz usunieta.\n";
	}
	//usuniecie listy sasiedztwa
	if (list != nullptr) {
		adjListElement* deletedV = nullptr;
		adjListElement* tempV = nullptr;

		for (int i = 0; i < V; i++) {
			tempV = list[i].head;
			while (tempV != nullptr) {
				deletedV = tempV;
				tempV = tempV->next;
				delete deletedV;
			}
		}

		delete [] list;
		list = nullptr;
		//cout << "Lista usunieta.\n";
	}
	//usuniecie pozosta³ych atrybutów grafu
	V = 0;
	E = 0;
	firstV = -1;
	lastV = -1;
}

Graph::~Graph()
{
	clearGraph();
}

//dodatkowa funkcja do generacji liczb pseudolosowych
//reprezentuj¹cych wagi
