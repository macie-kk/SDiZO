#pragma once

#include <string>
#include "Edge.h"
#include "List.h"
#include "Vertex.h"

using namespace std;

class Graf {
   private:
    int V;    // ilosc wierzcholkow
    int E;    // ilosc krawedzi
    int arg;  // argument opisujacy czy wierzcholek startowy, uzywany w tablicy d[i]

    int** macierzWag = nullptr;  // macierz wag
    Edge* krawedzie = nullptr;   // krawędzie
    List<Vertex> wierzcholki;

    // dla kruskala
    int* rank;
    Vertex* findSet(Vertex* v);
    int findSet(int w, int* parent);
    void unionSet(Vertex* v_1, Vertex* v_2);
    void unionSet(int w_1, int w_2, int* parent, int* rank);

   public:
    Graf();
    ~Graf();

    void bellmanFordList();
    void bellmanFordMatrix();

    void dijkstraList();
    void dijkstraMatrix();

    void primList();
    void primMatrix();

    void kruskalList();
    void kruskalMatrix();  // ZROBIĆ

    void loadFromFile(string Filename, bool mst = false);
    void generateGraf(int v, float den, bool directed);

    void display();

    int findIndex(Vertex* elem);

    void init();  // usuniecie istniejacej macierzy i wypelnienie nowej zerami wedlug ilosci wcztanych wyzej wierzcholkow
};
