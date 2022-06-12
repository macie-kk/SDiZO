#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Graf.h"
#include "Vertex.h"

using namespace std;

double timePassed(clock_t start_time) {
    return (((double)clock() - start_time) / CLOCKS_PER_SEC) * 1000;
}

void menuShortestPath() {
    char opt;
    Graf myGraf;
    string filename;
    clock_t start_time;

    system("clear");
    do {
        cout << endl;
        cout << "--- NAJKROTSZA SCIEZKA" << endl;
        cout << "1. Wczytaj graf z pliku" << endl;
        cout << "2. Wygeneruj graf" << endl;
        cout << "3. Wyswietl listowo i macierzowo" << endl;
        cout << "4. Algorytm Dijkstry" << endl;
        cout << "5. Algorytm Bellmana-Forda" << endl;
        cout << "0. Wstecz" << endl;

        cout << "\n> ";
        cin >> opt;
        cout << endl;

        int v, den;
        char directed;
        switch (opt) {
            case '1':
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                myGraf.loadFromFile(filename);
                break;

            case '2':
                cout << "Podaj ilosc wierzcholkow: ";
                cin >> v;
                cout << "Podaj gestosc: ";
                cin >> den;
                cout << "Skierowany? [y/n]: ";
                cin >> directed;

                myGraf.generateGraf(v, den, directed == 'y' || directed == 'Y');
                break;

            case '3':
                myGraf.display();
                break;

            case '4':
                myGraf.dijkstraMatrix();
                break;

            case '5':
                myGraf.bellmanFordList();
                break;
        }

    } while (opt != '0');
}

void menuMST() {
    char opt;
    Graf myGraf;
    string filename;
    clock_t start_time;

    system("clear");
    do {
        cout << endl;
        cout << "--- MST" << endl;
        cout << "1. Wczytaj graf z pliku" << endl;
        cout << "2. Wygeneruj graf" << endl;
        cout << "3. Wyswietl listowo i macierzowo" << endl;
        cout << "4. Algorytm Prima" << endl;
        cout << "5. Algorytm Kruskala" << endl;
        cout << "0. Wstecz" << endl;

        cout << "\n> ";
        cin >> opt;
        cout << endl;

        int v, den;
        char directed;
        switch (opt) {
            case '1':
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                myGraf.loadFromFile(filename, true);
                break;

            case '2':
                cout << "Podaj ilosc wierzcholkow: ";
                cin >> v;
                cout << "Podaj gestosc: ";
                cin >> den;

                myGraf.generateGraf(v, den, false);
                break;

            case '3':
                myGraf.display();
                break;

            case '4':
                myGraf.primMatrix();
                break;

            case '5':
                start_time = clock();
                myGraf.kruskalMatrix();
                break;
        }

    } while (opt != '0');
}

void mainMenu() {
    char option;

    system("clear");
    do {
        cout << endl;
        cout << "---- MENU GLOWNE" << endl;
        cout << "1. Najkrotsza droga" << endl;
        cout << "2. MST" << endl;
        cout << "0. Wyjscie" << endl;
        cout << "\n> ";
        cin >> option;
        cout << endl;

        switch (option) {
            case '1':
                menuShortestPath();
                break;

            case '2':
                menuMST();
                break;
        }

    } while (option != '0');
}

void logToFile(string metoda, int v, int den) {
    Graf myGraf;
    myGraf.generateGraf(v, den, false);

    ofstream MyFile("./results/" + metoda + "_" + to_string(v) + "_" + to_string(den) + ".txt");
    for (int i = 0; i < 100; i++) {
        clock_t start_time = clock();
        myGraf.bellmanFordMatrix();
        MyFile << to_string(timePassed(start_time)) << "\n";
    }
    MyFile.close();
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    mainMenu();

    // generowanie danych :: wymaga stworzenia folderu "results"
    // int v[] = {5, 10, 15, 20, 25};
    // int den[] = {25, 50, 75, 90};
    // string metoda = "bf_matrix";

    // for (int i = 0; i < (sizeof v / sizeof v[0]); i++) {
    //     for (int j = 0; j < (sizeof den / sizeof den[0]); j++) {
    //         logToFile(metoda, v[i], den[j]);
    //     }
    // }
    return 0;
}
