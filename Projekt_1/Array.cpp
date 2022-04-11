#include "Array.h"
#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Menu.h"
using namespace std;

Array::Array() {
    array = NULL;
    length = 0;
}

Array::~Array() {
    delete array;
}

void Array::pushIndex(int index, int value) {
    // przerwij funkcje jezeli index jest niepoprawny
    if (index > length || index < 0) {
        cout << "Indeks niepoprawny" << endl;
        return;
    }

    int *newArray = new int[length + 1];
    int j = 0;  // iterator dla starej tablicy

    // przekopiowanie elementow i dodanie nowego
    for (int i = 0; i <= length; i++) {
        if (i == index) {
            newArray[i] = value;
            continue;
        }
        newArray[i] = array[j++];
    }

    delete array;  // ustawienie nowej tablicy w miejsce starej
    array = newArray;
    length++;
}

void Array::pushFirst(int value) {
    int *newArray = new int[length + 1];
    newArray[0] = value;  // przypisanie pierwszego elementu

    // przekopiowanie elementow starej tablicy
    for (int i = 0; i < length; i++) {
        newArray[i + 1] = array[i];
    }

    delete array;
    array = newArray;
    length++;
}

void Array::pushLast(int value) {
    int *newArray = new int[length + 1];

    // przekopiowanie elementow starej tablicy
    for (int i = 0; i < length; i++) {
        newArray[i] = array[i];
    }
    newArray[length] = value;  // wstawienie ostatniego elementu

    delete array;
    array = newArray;
    length++;
}

void Array::popIndex(int index) {
    // sprawdzenie czy podany indeks nie wykracza poza zakres tablicy
    if (index > length || index < 0) {
        cout << "Indeks niepoprawny" << endl;
        return;
    }

    int *newArray = new int[length - 1];
    int j = 0;

    // przekopiowanie wszystkich elementow poza wskazanym
    for (int i = 0; i < length; i++) {
        if (i != index) {
            newArray[j++] = array[i];
        }
    }

    delete array;
    array = newArray;
    length--;
}

void Array::popFirst() {
    if (length > 0) {
        int *newArray = new int[--length];

        // przekopiowanie elementow poza pierwszym
        for (int i = 0; i < length; i++) {
            newArray[i] = array[i + 1];
        }

        delete array;
        array = newArray;
    }
}

void Array::popLast() {
    if (length > 0) {
        // utworzenie nowej tablicy
        int *newArray = new int[length - 1];
        // przekopiowanie elementow poza ostatnim
        for (int i = 0; i < length - 1; i++) {
            newArray[i] = array[i];
        }
        // zwolnienie pamieci
        delete array;
        // ustawienie nowej tablicy w miejsce starej
        array = newArray;
        // zmniejszenie dlugosc tablicy
        length--;
    }
}

int Array::findElement(int value) {
    // sprawdzenie czy istnieje element o podanej wartosci
    for (int i = 0; i < length; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;  // zwrocenie -1 jak nie znaleziono
}

void Array::replaceElement(int oldValue, int newValue) {
    // sprawdzenie pod jakim indeksem znajduje sie szukany element
    int index = findElement(oldValue);

    // jezeli znaleziono element to zamien
    if (index != -1) {
        array[index] = newValue;
        return;
    }
    cout << "Nie ma takiego elementu\n";  // w przeciwnym wypadku wypisz blad
}

void Array::popValue(int value) {
    // sprawdzenie pod jakim indeksem znajduje sie szukany element
    int index = findElement(value);

    // jezeli znaleziono element to usun
    if (index != -1) {
        popIndex(index);
    }
    cout << "Nie ma takiego elementu\n";  // w przeciwnym wypadku wypisz blad
}

void Array::loadNumbers() {
    fstream plik;
    plik.open("_sampleNumbers.txt", ios::in);
    plik >> length;

    // nadpisz stara tablice
    delete array;
    array = new int[length];

    // wpisz liczby z pliku do nowej
    for (int i = 0; i < length; i++) {
        plik >> array[i];
    }
    plik.close();
}

void Array::show() {
    cout << "Tablica : [";
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << "]\n";
    cout << "Ilosc elementow: " << length << endl;
}

void Array::clearArray() {
    delete array;
    array = NULL;
    length = 0;
}

void Array::testReplaceElement(std::ofstream &file, int amount) {
    clearArray();
    srand(time(NULL));

    file << "Replace; ";
    for (int i = 1; i <= amount; i++) {
        pushFirst(rand() % 100);

        cout << "\rTesting Replace: " << i;
        startTimer();
        replaceElement(array[rand() % length], rand() % 100);
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

void Array::testFindElement(std::ofstream &file, int amount) {
    clearArray();
    srand(time(NULL));

    file << "Wyszukaj; ";
    for (int i = 1; i <= amount; i++) {
        pushFirst(rand() % 100);

        cout << "\rTesting Find: " << i;
        startTimer();
        findElement(array[rand() % length]);
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

void Array::testPopFirst(std::ofstream &file, int amount) {
    srand(time(NULL));

    file << "Pop First; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting pop first: " << i;
        startTimer();
        popFirst();
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

void Array::testPopLast(std::ofstream &file, int amount) {
    srand(time(NULL));

    file << "Pop Last; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting pop last: " << i;
        startTimer();
        popLast();
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

void Array::testPushLast(std::ofstream &file, int amount) {
    srand(time(NULL));

    file << "Push Last; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting push last: " << i;
        startTimer();
        pushLast(rand() % 100);
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

void Array::testPushIndex(std::ofstream &file, int amount) {
    clearArray();
    srand(time(NULL));

    file << "Push Index; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting push index: " << i;
        if (i == 1) {
            pushFirst(96);
            continue;
        }
        startTimer();
        pushIndex(rand() % length, 69);
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

void Array::testPushFirst(std::ofstream &file, int amount) {
    srand(time(NULL));

    file << "Push First; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting push first: " << i;
        startTimer();
        pushFirst(rand() % 100);
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

void Array::runTests(int amount) {
    std::filesystem::create_directory("./tests");
    std::ofstream fileOut;
    fileOut.open("./tests/ArrayTest.csv", std::ios_base::app);

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

    testPushFirst(fileOut, amount);
    testPopFirst(fileOut, amount);
    testPushLast(fileOut, amount);
    testPopLast(fileOut, amount);
    testFindElement(fileOut, amount);
    testPushIndex(fileOut, amount);
    fileOut.close();
    clearArray();
}
