#include "Graf.h"
#include <climits>
#include <fstream>
#include <iostream>
#include "Heap.h"

Graf::Graf() {}

Graf::~Graf() {}

void Graf::dijkstraMatrix() {
    if (macierzWag != nullptr) {
        int* d = new int[V];  // inicjalizacja tablic wynikowych algorytmu
        int* p = new int[V];

        for (int i = 0; i < V; i++) {  // wypelnienie tablic poczatkowymi wartosciami
            d[i] = INT_MAX;
            p[i] = -1;
        }

        d[arg] = 0;       // wierzcholek startowy
        Heap<int*> Q(V);  // kolejka priorytetowa w postaci kopca minimalnego

        for (int i = 0; i < V; i++) {
            Q.insert(&d[i]);
        }

        int u;

        while (Q.getLength() != 0) {
            for (u = 0; u < V; u++) {
                if (&d[u] == Q.getTop()) {
                    break;
                }
            }

            for (int i = 0; i < V; i++) {
                if (macierzWag[i][u] != 0 && d[u] != INT_MAX && d[i] > d[u] + macierzWag[i][u]) {  // relaksacja
                    d[i] = d[u] + macierzWag[i][u];
                    p[i] = u;
                }
            }

            Q.deleteElement(0);
        }

        // Wyniki algorytmu
        cout << "Tablica d[i]: " << endl;
        cout << "Indeks: ";
        for (int i = 0; i < V; i++)
            cout << i << " ";
        cout << endl;
        cout << "Dystans:";

        for (int i = 0; i < V; i++) {
            cout << d[i] << " ";
        }

        cout << endl
             << "\nTablica p[i]: " << endl;
        cout << "Indeks: ";
        for (int i = 0; i < V; i++)
            cout << i << " ";
        cout << endl;
        cout << "Rodzic: ";

        for (int i = 0; i < V; i++) {
            cout << p[i] << " ";
        }

        cout << endl;
        delete[] p;
        delete[] d;
    } else
        cout << "Przed proba wykonania algorytmu wczytaj graf!" << endl;
}

void Graf::bellmanFordList() {
    bool updated;
    List<EdgeClass*> edges;

    wierzcholki[arg].setDistanceFromStart(0);

    //ładowanie wszystskich krawędzi
    for (int i = 0; wierzcholki.size() > i; i++) {
        for (int j = 0; wierzcholki[i].getNeighboursList().size() > j; j++) {
            edges.AddBack(&(wierzcholki[i].getNeighboursList()[j]));
        }
    }

    for (int i = 0; i < V - 1; i++) {
        updated = false;

        for (int j = 0; j < E; j++) {
            if (edges[j]->get_src()->getDistanceFromStart() != INT_MAX && edges[j]->get_src()->getDistanceFromStart() + edges[j]->get_weight() < edges[j]->get_dst()->getDistanceFromStart()) {
                edges[j]->get_dst()->setDistanceFromStart(edges[j]->get_src()->getDistanceFromStart() + edges[j]->get_weight());
                edges[j]->get_dst()->setParent(edges[j]->get_src());
                updated = true;
            }
        }

        if (updated == false)  // sprawdzenie czy jest sens dalej iterowac
            break;
    }

    for (int i = 0; i < E && updated; i++) {  // petla sprawdzajaca czy wystepuje ujemny cykl w grafie
        if (edges[i]->get_src()->getDistanceFromStart() != INT_MAX && edges[i]->get_src()->getDistanceFromStart() + edges[i]->get_weight() < edges[i]->get_dst()->getDistanceFromStart()) {
            cout << "Ujemny cykl!" << endl;
            return;
        }
    }

    for (int i = 0; V > i; i++) {
        cout << "Vertex: " << i << endl;
        cout << "Distance from start: " << wierzcholki[i].getDistanceFromStart() << endl;
        cout << "Parent: " << findIndex(wierzcholki[i].getParent()) << endl
             << endl;
    }
}

void Graf::bellmanFordMatrix() {
    if (macierzWag != nullptr) {
        int* d = new int[V];  // inicjalizacja tablic wynikowych algorytmu
        int* p = new int[V];

        for (int i = 0; i < V; i++) {  // wypelnienie tablic poczatkowymi wartosciami
            d[i] = INT_MAX;
            p[i] = -1;
        }

        bool updated;  // flaga sprawdzajaca czy nastapila relaksacja

        d[arg] = 0;  // wierzcholek startowy

        for (int i = 0; i < V - 1; i++) {  // iteracja po wszystkich mozliwych sasiadach
            updated = false;

            for (int j = 0; j < E; j++) {                                                                              // E = liczba krawedzi
                if (d[krawedzie[j].src] == INT_MAX && d[krawedzie[j].src] + krawedzie[j].cst < d[krawedzie[j].dst]) {  // relaksacja
                    d[krawedzie[j].dst] = d[krawedzie[j].src] + krawedzie[j].cst;
                    p[krawedzie[j].dst] = krawedzie[j].src;
                    updated = true;
                }
            }

            if (updated == false)  // sprawdzenie czy jest sens dalej iterowac
                break;
        }

        for (int i = 0; i < E && updated; i++) {  // petla sprawdzajaca czy wystepuje ujemny cykl w grafie
            if (d[krawedzie[i].src] == INT_MAX && d[krawedzie[i].src] + krawedzie[i].cst < d[krawedzie[i].dst]) {
                cout << "Ujemny cykl!" << endl;
                return;
            }
        }

        // Wyniki algorytmu
        cout << "Tablica d[i]: " << endl;
        cout << "Indeks: ";
        for (int i = 0; i < V; i++)
            cout << i << " ";
        cout << endl;
        cout << "Dystans:";

        for (int i = 0; i < V; i++) {  // wypisywanie d[i]
            cout << d[i] << " ";
        }

        cout << endl
             << "Tablica p[i]: " << endl;
        cout << "Indeks: ";
        for (int i = 0; i < V; i++)
            cout << i << " ";
        cout << endl;
        cout << "Rodzic: ";

        for (int i = 0; i < V; i++) {  // wypisywanie p[i]
            cout << p[i] << " ";
        }

        cout << endl;
        delete[] p;
        delete[] d;
    } else
        cout << "Przed proba wykonania algorytmu wczytaj graf!" << endl;
}

void Graf::dijkstraList() {
    Heap<Vertex*> heapQueue(V);

    wierzcholki[arg].setDistanceFromStart(0);

    for (int i = 0; V > i; i++) {
        heapQueue.insert(&(wierzcholki[i]));
    }

    Vertex* currentVertex;
    EdgeClass* currentNeighbourStruct;

    while (heapQueue.getLength() > 0) {
        currentVertex = heapQueue.getTop();

        for (int i = 0; currentVertex->getNeighboursList().size() > i; i++) {
            currentNeighbourStruct = &currentVertex->getNeighboursList()[i];

            if (currentNeighbourStruct->get_dst()->getDistanceFromStart() >
                currentVertex->getDistanceFromStart() + currentNeighbourStruct->get_weight()) {
                currentNeighbourStruct->get_dst()->setDistanceFromStart(currentVertex->getDistanceFromStart() + currentNeighbourStruct->get_weight());
                currentNeighbourStruct->get_dst()->setParent(currentVertex);
            }
        }

        heapQueue.deleteElement(0);
    }

    for (int i = 0; V > i; i++) {
        cout << "Vertex: " << i << endl;
        cout << "Distance from start: " << wierzcholki[i].getDistanceFromStart() << endl;
        cout << "Parent: " << findIndex(wierzcholki[i].getParent()) << endl
             << endl;
    }
}

void Graf::primList() {
    Heap<Vertex*> heapQueue(V);
    bool* mstSet = new bool[V];

    // kluczem jest dystans od startowego wierzchołka
    wierzcholki[arg].setDistanceFromStart(0);

    for (int i = 0; V > i; i++) {
        heapQueue.insert(&(wierzcholki[i]));
    }

    Vertex* currentVertex;
    EdgeClass* currentEdgeStruct;

    while (heapQueue.getLength() > 0) {
        currentVertex = heapQueue.getTop();

        mstSet[findIndex(currentVertex)] = true;

        cout << "Current: " << findIndex(currentVertex) << endl;

        for (int i = 0; V > i; i++) {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; V > i; i++) {
            cout << wierzcholki[i].getDistanceFromStart() << " ";
        }

        cout << endl;

        for (int i = 0; V > i; i++) {
            cout << findIndex(wierzcholki[i].getParent()) << " ";
        }

        cout << endl
             << endl;

        for (int i = 0; currentVertex->getNeighboursList().size() > i; i++) {
            currentEdgeStruct = &currentVertex->getNeighboursList()[i];

            cout << "Checking vertex: " << findIndex(currentEdgeStruct->get_dst()) << endl;

            if (mstSet[findIndex(currentEdgeStruct->get_dst())] == false &&
                currentEdgeStruct->get_weight() < currentEdgeStruct->get_dst()->getDistanceFromStart()) {  // relaksacja
                currentEdgeStruct->get_dst()->setDistanceFromStart(currentEdgeStruct->get_weight());
                currentEdgeStruct->get_dst()->setParent(currentVertex);
            }
        }

        heapQueue.deleteElement(0);
    }

    int sum = 0;

    for (int i = 0; V > i; i++) {
        cout << "Vertex: " << i << endl;
        cout << "Distance from start: " << wierzcholki[i].getDistanceFromStart() << endl;
        cout << "Parent: " << findIndex(wierzcholki[i].getParent()) << endl
             << endl;

        sum += wierzcholki[i].getDistanceFromStart();
    }

    cout << "Suma MST: " << sum << endl;
}

void Graf::primMatrix() {
    int* p = new int[V];    // rodzice
    int* key = new int[V];  // tablica najmniejszych wartosci krawedzi wierzcholka
    Heap<int*> Q(V);        // kolejka priorytetowa w postaci kopca
    bool* mstSet = new bool[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        p[i] = -1;
        mstSet[i] = false;
    }

    key[0] = 0;  // wierzcholek startowy
    p[0] = -1;   // wierzcholek startowy nie ma rodzica

    for (int i = 0; i < V; i++) {  // zapełnienie kopca
        Q.insert(&key[i]);
    }

    int u;

    while (Q.getLength() != 0) {
        for (u = 0; u < V; u++) {
            if (&key[u] == Q.getTop()) {
                break;
            }
        }

        mstSet[u] = true;

        for (int i = 0; i < V; i++) {
            if (mstSet[i] == false && macierzWag[u][i] != 0 && key[u] != INT_MAX && key[i] > macierzWag[u][i])  // relaksacja
            {
                key[i] = macierzWag[u][i];
                p[i] = u;
            }
        }

        Q.deleteElement(0);
    }

    int mstValue = 0;

    // Wyniki algorytmu
    for (int i = 0; i < V; i++) {
        mstValue += key[i];
    }

    cout << "Waga MST: " << mstValue << endl;
    cout << "Rodzic[i]: ";

    for (int i = 0; i < V; i++) {
        cout << p[i] << " ";
    }

    cout << endl;

    delete[] p;
    delete[] key;
}

Vertex* Graf::findSet(Vertex* v) {
    if (v->getParent() != v)
        v->setParent(findSet(v->getParent()));

    return v->getParent();
}

int Graf::findSet(int w, int* parent) {
    if (parent[w] != w)
        parent[w] = findSet(parent[w], parent);

    return parent[w];
}

void Graf::unionSet(Vertex* v_1, Vertex* v_2) {
    Vertex* a = this->findSet(v_1);
    Vertex* b = this->findSet(v_2);

    if (a->getRank() < b->getRank()) {
        for (int i = 0; wierzcholki.size() > i; i++) {
            if (wierzcholki[i].getParent() == a) {
                wierzcholki[i].setParent(b);
            }
        }

        b->setRank(b->getRank() + 1);
    } else {
        for (int i = 0; wierzcholki.size() > i; i++) {
            if (wierzcholki[i].getParent() == b) {
                wierzcholki[i].setParent(a);
            }
        }

        a->setRank(a->getRank() + 1);
    }
}

void Graf::unionSet(int w_1, int w_2, int* parent, int* rank) {
    int a = findSet(w_1, parent);
    int b = findSet(w_2, parent);

    if (rank[a] < rank[b]) {
        for (int i = 0; V > i; i++) {
            if (parent[i] == a) {
                parent[i] = b;
            }
        }

        rank[b] += 1;
    } else {
        for (int i = 0; V > i; i++) {
            if (parent[i] == b) {
                parent[i] = a;
            }
        }

        rank[a] += 1;
    }
}

void Graf::kruskalList() {
    rank = new int[V];
    Heap<EdgeClass*> edges(E);
    List<EdgeClass*> mst;

    for (int i = 0; V > i; i++) {
        rank[i] = 0;
    }

    for (int i = 0; wierzcholki.size() > i; i++) {
        wierzcholki[i].setParent(&wierzcholki[i]);

        for (int j = 0; wierzcholki[i].getNeighboursList().size() > j; j++) {
            edges.insert(&(wierzcholki[i].getNeighboursList()[j]));
        }
    }

    Vertex* v_1;
    Vertex* v_2;

    while (!edges.isEmpty()) {
        v_1 = edges.getTop()->get_src();
        v_2 = edges.getTop()->get_dst();

        if (v_1->getParent() != v_2->getParent()) {
            mst.AddBack(edges.getTop());
            this->unionSet(v_1, v_2);
        }

        edges.deleteElement(0);
    }

    int sum = 0;

    for (int i = 0; mst.size() > i; i++) {
        cout << findIndex(mst[i]->get_src()) << " -> " << findIndex(mst[i]->get_dst()) << ": " << mst[i]->get_weight() << endl;
        sum += mst[i]->get_weight();
    }

    cout << "\nSuma MST: " << sum << endl;
}

void Graf::kruskalMatrix() {
    rank = new int[V];
    List<Edge*> mst;
    Heap<Edge*> edges(E);

    int* d = new int[V];
    int* p = new int[V];

    // dodanie wszystkich krawędzi do kopca
    for (int i = 0; i < E; i++) {
        edges.insert(&(krawedzie[i]));
    }

    // ustawienie początkowe wartości
    for (int i = 0; i < V; i++) {
        d[i] = INT_MAX;
        p[i] = i;
        rank[i] = 0;
    }

    // obecnie sprawdzane wierzchołki
    int w_1;
    int w_2;

    while (!edges.isEmpty()) {
        w_1 = edges.getTop()->src;
        w_2 = edges.getTop()->dst;

        if (p[w_1] != p[w_2]) {
            mst.AddBack(edges.getTop());
            this->unionSet(w_1, w_2, p, rank);
        }

        edges.deleteElement(0);
    }

    int sum = 0;

    for (int i = 0; mst.size() > i; i++) {
        cout << mst[i]->src << " -> " << mst[i]->dst << ": " << mst[i]->cst << endl;
        sum += mst[i]->cst;
    }

    cout << "Suma MST: " << sum << endl;
}

void Graf::loadFromFile(string filename, bool mst) {
    ifstream plik(filename);

    if (!plik.good()) {
        cout << "Nie znaleziono pliku\n";
        return;
    }

    plik >> E;
    plik >> V;

    if (!mst) {
        plik >> arg;
    }

    this->init();  // usuniecie istniejacej macierzy i wypelnienie nowej zerami wedlug ilosci wczytanych wyzej wierzcholkow

    int start, end, cost;

    for (int i = 0; !plik.eof(); i++) {
        plik >> start;
        plik >> end;
        plik >> cost;

        if (plik.eof())
            break;

        macierzWag[start][end] = cost;
        wierzcholki[start].addNeighbour(&wierzcholki[start], &wierzcholki[end], cost);

        if (mst) {
            macierzWag[end][start] = cost;
            wierzcholki[end].addNeighbour(&wierzcholki[end], &wierzcholki[start], cost);
        }

        krawedzie[i].src = start;
        krawedzie[i].dst = end;
        krawedzie[i].cst = cost;
    }
}

// den: 0-100 (%)
void Graf::generateGraf(int v, float den, bool directed) {
    this->arg = 0;
    this->V = v;

    den /= 100;
    int maxE = V * (V - 1);  // ilosc krawedzi ze wzoru w oparciu na gestosc grafu

    if (!directed)
        maxE /= 2;

    E = floor(den * maxE);
    this->init();  // usuniecie istniejacej macierzy i wypelnienie nowej zerami wedlug ilosci wcztanych wyzej wierzcholkow

    int V1, V2, cost;
    bool* mark = new bool[V];

    for (int i = 0; V > i; i++) {
        mark[i] = false;
    }

    bool all_visited = false;

    for (int i = 0; E > i; i++) {
        // sprawdzanie czy wszystkie wierzchołki mają już połączenie
        all_visited = true;

        for (int i = 0; V > i; i++) {
            if (mark[i] == false) {
                all_visited = false;
                break;
            }
        }

        if (all_visited) {
            for (int i = 0; V > i; i++) {
                mark[i] = false;
            }
        }

        do {
            V1 = rand() % V;
            while ((V2 = rand() % V) == V1) {
            }
        } while (macierzWag[V1][V2] != 0 || mark[V1] != false);

        cost = rand() % 9 + 1;
        macierzWag[V1][V2] = cost;
        wierzcholki[V1].addNeighbour(&wierzcholki[V1], &wierzcholki[V2], cost);

        if (!directed) {
            macierzWag[V2][V1] = cost;
        }

        mark[V1] = true;
    }

    int counter = 0;

    for (int i = 1; V > i; i++) {
        for (int j = 0; i > j; j++) {
            if (macierzWag[i][j] != 0) {
                krawedzie[counter].src = i;
                krawedzie[counter].dst = j;
                krawedzie[counter].cst = macierzWag[i][j];
                counter++;
            }
        }
    }
}

void Graf::display() {
    if (macierzWag != nullptr) {
        cout << "\nMacierz wag:" << endl;

        for (int i = 0; i < V; i++) {  // reprezentacja macierzowa
            for (int j = 0; j < V; j++) {
                cout << macierzWag[i][j];
                cout << " ";
            }
            cout << endl;
        }

        cout << "\nKrawedzie:" << endl;

        for (int i = 0; i < E; i++) {
            if (krawedzie[i].src == 0 && krawedzie[i].dst == 0 && krawedzie[i].cst == 0) {
                continue;
            }
            cout << krawedzie[i].src << " -> " << krawedzie[i].dst << " = " << krawedzie[i].cst << endl;
        }
    } else
        cout << "Nie mozna wyswietlic reprezentacji, wczytaj graf!" << endl;
}

void Graf::init() {
    if (macierzWag != nullptr) {  // uswanie istniejacej macierzy
        for (int i = 0; i < V; i++) {
            delete[] macierzWag[i];
        }
        delete macierzWag;
        macierzWag = nullptr;
    }

    macierzWag = new int*[V];
    for (int i = 0; i < V; i++) {
        macierzWag[i] = new int[V];
        for (int j = 0; j < V; j++) {  // wypelnienie zerami
            macierzWag[i][j] = 0;
        }
    }

    // tworzenie tabeli krawędzi
    if (krawedzie != nullptr) {
        delete[] krawedzie;
        krawedzie = nullptr;
    }

    krawedzie = new Edge[E];

    for (int i = 0; V > i; i++) {
        wierzcholki.AddBack(Vertex());
    }
}

int Graf::findIndex(Vertex* elem) {
    for (int i = 0; wierzcholki.size() > i; i++) {
        if (&(wierzcholki[i]) == elem)
            return i;
    }
    return -1;
}
