#include "Table.h"
#include <curses.h>
#include <time.h>
#include <fstream>
#include <iostream>

using namespace std;

Table::Table() {
    tab = nullptr;
    cnt = 0;
}

Table::~Table() {
    destroyTable();
}

void Table::destroyTable() {
    if (tab != nullptr)
        delete[] tab;

    cnt = 0;
}

void Table::deleteFromTable(int index) {
    int* tmp_tab = new int[cnt - 1];

    if (index < cnt) {
        for (int i = 0; index > i; i++) {
            tmp_tab[i] = tab[i];
        }

        for (int i = index; (cnt - 1) > i; i++) {
            tmp_tab[i] = tab[i + 1];
        }
        if (tab != nullptr)
            delete[] tab;

        tab = tmp_tab;
        cnt--;
    }
}

void Table::display() {
    for (int i = 0; i < cnt; i++) {
        cout << tab[i] << " ";
    }
}

void Table::generateTable(int size) {
    tab = new int[size];

    for (int i = 0; i < size; i++) {
        AddAtIndex((rand() % 100), i);
    }
}

void Table::loadFromFile(string Filename) {
    destroyTable();

    int size, value;
    ifstream plik(Filename);

    if (plik.is_open()) {
        plik >> size;

        // tworzenie tablicy dynamicznej
        tab = new int[size];

        for (int i = 0; size > i; i++) {
            plik >> value;
            AddAtIndex(value, i);
        }

        plik.close();
    } else {
        cout << "Nie znaleziono pliku\n";
    }
}

bool Table::IsValueInTable(int val) {
    for (int i = 0; i < cnt; i++) {
        if (tab[i] == val)
            return true;
    }

    return false;
}

void Table::AddFront(int val) {
    int* tmp_tab = new int[cnt + 1];

    for (int i = 1; (cnt + 1) > i; i++) {
        tmp_tab[i] = tab[i - 1];
    }

    tmp_tab[0] = val;

    if (tab != nullptr)
        delete[] tab;

    tab = tmp_tab;
    cnt++;
}

void Table::AddBack(int val) {
    int* tmp_tab = new int[cnt + 1];

    for (int i = 0; cnt > i; i++) {
        tmp_tab[i] = tab[i];
    }

    tmp_tab[cnt] = val;

    if (tab != nullptr)
        delete[] tab;

    tab = tmp_tab;
    cnt++;
}

void Table::AddRandom(int val) {
    int* tmp_tab = new int[cnt + 1];
    int rand_index = rand() % (cnt + 1);

    for (int i = 0; rand_index > i; i++) {
        tmp_tab[i] = tab[i];
    }

    tmp_tab[rand_index] = val;

    for (int i = rand_index + 1; (cnt + 1) > i; i++) {
        tmp_tab[i] = tab[i - 1];
    }

    if (tab != nullptr)
        delete[] tab;

    tab = tmp_tab;
    cnt++;
}

void Table::AddAtIndex(int val, int index) {
    if (index <= cnt && index >= 0) {
        int* tmp_tab = new int[cnt + 1];

        for (int i = 0; index > i; i++) {
            tmp_tab[i] = tab[i];
        }

        tmp_tab[index] = val;

        for (int i = index + 1; (cnt + 1) > i; i++) {
            tmp_tab[i] = tab[i - 1];
        }

        if (tab != nullptr)
            delete[] tab;

        tab = tmp_tab;
        cnt++;
    }
}
