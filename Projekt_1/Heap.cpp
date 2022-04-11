#include "Heap.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Menu.h"
using namespace std;

Heap::Heap() {
    array = NULL;
    length = 0;
}

Heap::~Heap() {
    delete array;
}

void Heap::push(int value) {
    int *newArray = new int[length + 1];  // utworzenie nowej tablicy kopca
    // przekopiowanie elementow starej tablicy kopca
    for (int i = 0; i < length; i++) {
        newArray[i] = array[i];
    }

    newArray[length] = value;  // wstawienie ostatniego elementu
    delete array;
    array = newArray;
    length++;
    fixUp(length - 1);
}

void Heap::pop(int value) {
    int index = findValue(value);

    if (index < 0) {
        cout << "Nie ma takiego elementu" << endl;
        return;
    }

    array[index] = array[length - 1];

    int *newArray = new int[length - 1];
    // przekopiowanie elementow poza ostatnim
    for (int i = 0; i < length - 1; i++) {
        newArray[i] = array[i];
    }

    delete array;
    array = newArray;
    length--;
    fixDown(index);
    fixUp(index);
}

int Heap::findValue(int value) {
    for (int i = 0; i < length; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

// naprawa kopca w gore
void Heap::fixUp(int index) {
    if (index < length && index >= 0) {
        // sprawdzenie czy dziecko ma wieksza wartosc niz rodzic, zamiana jesli tak
        if (array[index] > array[(index - 1) / 2]) {
            int temp = array[index];
            array[index] = array[(index - 1) / 2];
            array[(index - 1) / 2] = temp;
            fixUp((index - 1) / 2);  // naprawa w gore
        }
    }
}

void Heap::fixDown(int index) {
    if ((2 * index + 1) < length) {
        int parent = array[index];
        int childOne = array[2 * index + 1];
        int childTwo;

        childTwo = (2 * index + 2 < length) ? array[2 * index + 2] : childOne;

        if (childOne > parent || childTwo > parent) {
            int incr = childOne >= childTwo ? 1 : 2;
            int temp = array[index];
            array[index] = array[2 * index + incr];
            array[2 * index + incr] = temp;
            fixDown(2 * index + incr);  // dalsza naprawa kopca w dol
        }
    }
}

// rekurencyjna funkcja wyswietlajaca kopiec poziomo
void Heap::showRec(const string &prefix, int index) {
    if (index >= length) {
        return;
    }

    bool isLeft = index % 2 != 0;
    cout << prefix;
    cout << (isLeft ? "|--" : "\\--");
    cout << array[index] << endl;

    // przejscie po galeziach kopcach wedlug wzoru na lewy i prawy element
    showRec(prefix + (isLeft ? "|   " : "    "), index * 2 + 1);
    showRec(prefix + (isLeft ? "|   " : "    "), index * 2 + 2);
}

void Heap::show() {
    showRec("", 0);  // rozpoczecie wyswietlanie kopcja od zerowego elementu bez prefixu
}

void Heap::loadNumbers() {
    delete array;
    array = NULL;
    length = 0;

    int amount;
    int value;

    fstream plik;
    plik.open("_sampleNumbers.txt", ios::in);
    plik >> amount;

    for (int i = 0; i < amount; i++) {
        plik >> value;
        push(value);
    }
    plik.close();
}

void Heap::clearHeap() {
    delete array;
    array = NULL;
    length = 0;
}

void Heap::testFindVal(std::ofstream &file, int amount) {
    clearHeap();
    srand(time(NULL));

    file << "Wyszukaj; ";
    for (int i = 1; i <= amount; i++) {
        push(rand() % 100);
        cout << "\rTesting Find: " << i;
        startTimer();
        findValue(array[rand() % length]);
        endTimer();

        if (i % 5 == 0) {
            string strResult = to_string(getPerformance());
            replace(strResult.begin(), strResult.end(), '.', ',');
            file << strResult;
            if (i != amount) {
                file << "; ";
            }
        }
    }
    cout << endl;
    file << endl;
}

void Heap::testPop(std::ofstream &file, int amount) {
    srand(time(NULL));

    file << "Pop; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting Pop: " << i;
        startTimer();
        pop(array[rand() % length]);
        endTimer();

        if (i % 5 == 0) {
            string strResult = to_string(getPerformance());
            replace(strResult.begin(), strResult.end(), '.', ',');
            file << strResult;
            if (i != amount) {
                file << "; ";
            }
        }
    }
    cout << endl;
    file << endl;
}

void Heap::testPush(std::ofstream &file, int amount) {
    srand(time(NULL));

    file << "Push; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting Push: " << i;
        startTimer();
        push(rand() % 100);
        endTimer();

        if (i % 5 == 0) {
            string strResult = to_string(getPerformance());
            replace(strResult.begin(), strResult.end(), '.', ',');
            file << strResult;
            if (i != amount) {
                file << "; ";
            }
        }
    }
    cout << endl;
    file << endl;
}

void Heap::runTests(int amount) {
    filesystem::create_directory("./tests");
    std::ofstream fileOut;
    fileOut.open("./tests/HeapTest.csv", std::ios_base::app);

    fileOut << "n; ";
    for (int i = 0; i <= amount; i += 5) {
        if (i == 0) continue;
        fileOut << i << "; ";
    }
    fileOut << endl;

    fileOut << "n-rev; ";
    for (int i = amount; i > 0; i -= 5) {
        fileOut << i << "; ";
    }
    fileOut << endl;

    testPush(fileOut, amount);
    testPop(fileOut, amount);
    testFindVal(fileOut, amount);
    fileOut.close();
    clearHeap();
}
