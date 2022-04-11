#include "Menu.h"
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include "Array.h"
#include "Heap.h"
#include "List.h"
#include "ListElement.h"

using namespace std;

chrono::_V2::system_clock::time_point performanceCountStart;
chrono::_V2::system_clock::time_point performanceCountEnd;

chrono::_V2::system_clock::time_point getCurrentTime() {
    return chrono::high_resolution_clock::now();
}

void clearConsole() {
    cout << "\x1b[2J\x1b[H";
}

void startTimer() {
    performanceCountStart = getCurrentTime();
}

void endTimer() {
    performanceCountEnd = getCurrentTime();
}

double getPerformance() {
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(performanceCountEnd - performanceCountStart);
    return elapsed.count() / 1000000.0;
}

void options() {
    clearConsole();
    cout << "Maciej Kazmierczyk - 259158\n\n";
    cout << "0. Koniec\n";
    cout << "1. Tablica\n";
    cout << "2. Lista\n";
    cout << "3. Kopiec\n";
    cout << "4. Generator liczb do pliku\n";
    cout << "\n>> Wybor: ";
}

void menuArray() {
    Array *array = new Array();
    int value, index, oldValue, choice = 1;

    while (choice) {
        clearConsole();
        array->show();

        cout << endl;
        cout << "0.  Koniec\n";
        cout << "1.  Dodaj na poczatek\n";
        cout << "2.  Dodaj na koniec\n";
        cout << "3.  Dodaj w wybrane miejsce\n";
        cout << "4.  Usun z poczatku\n";
        cout << "5.  Usun z konca\n";
        cout << "6.  Usun z wybranego miejsca\n";
        cout << "7.  Usun wartosc\n";
        cout << "8.  Wyszukaj wartosc\n";
        cout << "9.  Zamien wartosc\n";
        cout << "10. Zaladuj dane z pliku\n";
        cout << "11. Uruchom testy\n";
        cout << "12. Wyczysc\n";
        cout << "\n>>  Wybor: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Dodaj na poczatek wartosc: ";
                cin >> value;

                startTimer();
                array->pushFirst(value);
                endTimer();
                break;

            case 2:
                cout << "Dodaj na koniec wartosc: ";
                cin >> value;

                startTimer();
                array->pushLast(value);
                endTimer();
                break;

            case 3:
                cout << "Dodaj w miejscu [index]: ";
                cin >> index;
                cout << "Wartosc: ";
                cin >> value;

                startTimer();
                array->pushIndex(index, value);
                endTimer();
                break;

            case 4:
                startTimer();
                array->popFirst();
                endTimer();
                break;

            case 5:
                startTimer();
                array->popLast();
                endTimer();
                break;

            case 6:
                cout << "Usun wartosc z miejsca [index]:";
                cin >> index;

                startTimer();
                array->popIndex(index);
                endTimer();
                break;

            case 7:
                cout << "Usun wartosc: ";
                cin >> value;

                startTimer();
                array->popValue(value);
                endTimer();
                break;

            case 8:
                cout << "Wyszukaj wartosc: ";
                cin >> value;

                if (array->findElement(value) == -1) {
                    cout << "Nie znaleziono\n";
                    break;
                }

                cout << "Znaleziono pod indeksem: [";
                startTimer();
                array->findElement(value);
                endTimer();
                cout << array->findElement(value) << "]\n";
                break;

            case 9:
                cout << "Wartosc do zamiany: ";
                cin >> oldValue;
                cout << "Nowa wartosc: ";
                cin >> value;

                startTimer();
                array->replaceElement(oldValue, value);
                endTimer();
                break;

            case 10:
                startTimer();
                array->loadNumbers();
                endTimer();
                break;

            case 11: {
                int n;
                cout << "Podaj n: ";
                cin >> n;
                array->runTests(n);
            } break;

            case 12:
                startTimer();
                array->clearArray();
                endTimer();
                break;
        }

        cout << "\nCzas: " << getPerformance() << " ms\n";
        cout << "Enter" << endl;
        cin.get();
        cin.get();
    }

    delete array;
}

void menuList() {
    List *list = new List();
    int value, index, oldValue, choice = 1;

    while (choice) {
        clearConsole();
        list->show();

        cout << endl;
        cout << "0.  Koniec\n";
        cout << "1.  Dodaj na poczatek\n";
        cout << "2.  Dodaj na koniec\n";
        cout << "3.  Dodaj w wybrane miejsce\n";
        cout << "4.  Usun z poczatku\n";
        cout << "5.  Usun z konca\n";
        cout << "6.  Usun z wybranego miejsca\n";
        cout << "7.  Usun wartosc\n";
        cout << "8.  Wyszukaj wartosc\n";
        cout << "9.  Zamien wartosc\n";
        cout << "10. Zaladuj dane z pliku\n";
        cout << "11. Uruchom testy\n";
        cout << "12. Wyczysc\n";
        cout << "\n>>  Wybor: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Dodaj na poczatek wartosc: ";
                cin >> value;

                startTimer();
                list->pushFirst(value);
                endTimer();
                break;

            case 2:
                cout << "Dodaj na koniec wartosc: ";
                cin >> value;

                startTimer();
                list->pushLast(value);
                endTimer();
                break;

            case 3:
                cout << "Dodaj w miejscu [index]: ";
                cin >> index;
                cout << "Wartosc: ";
                cin >> value;

                startTimer();
                list->pushIndex(value, index);
                endTimer();
                break;

            case 4:
                startTimer();
                list->popFirst();
                endTimer();
                break;

            case 5:
                startTimer();
                list->popLast();
                endTimer();
                break;

            case 6:
                cout << "Usun wartosc z miejsca [index]: ";
                cin >> index;

                startTimer();
                list->popIndex(index);
                endTimer();
                break;

            case 7:
                cout << "Usun wartosc: ";
                cin >> value;

                startTimer();
                list->popValue(value);
                endTimer();
                break;

            case 8:
                cout << "Wyszukaj wartosc: ";
                cin >> value;
                list->searchElement(value);
                startTimer();
                list->findElement(value);
                endTimer();
                break;

            case 9:
                cout << "Wartosc do zamiany: ";
                cin >> oldValue;
                cout << "Nowa wartosc: ";
                cin >> value;

                startTimer();
                list->replaceElement(oldValue, value);
                endTimer();
                break;

            case 10:
                startTimer();
                list->loadNumbers();
                endTimer();
                break;

            case 11: {
                int n;
                cout << "Podaj n: ";
                cin >> n;
                list->runTests(n);
            } break;

            case 12:
                startTimer();
                list->clearList();
                endTimer();
                break;
        }

        cout << "\nCzas: " << getPerformance() << " ms\n";
        cout << "Enter" << endl;
        cin.get();
        cin.get();
    }

    delete list;
}

void menuHeap() {
    Heap *heap = new Heap();
    int value, choice = 1;

    while (choice) {
        clearConsole();
        heap->show();

        cout << endl;
        cout << "0. Koniec\n";
        cout << "1. Dodaj wartosc\n";
        cout << "2. Usun wartosc\n";
        cout << "3. Wyszukaj wartosc\n";
        cout << "4. Zaladuj dane z pliku\n";
        cout << "5. Uruchom testy\n";
        cout << "6. Wyczysc\n";
        cout << "\n>> Wybor: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Dodaj wartosc: ";
                cin >> value;

                startTimer();
                heap->push(value);
                endTimer();
                break;

            case 2:
                cout << "Usun wartosc: ";
                cin >> value;

                startTimer();
                heap->pop(value);
                endTimer();
                break;

            case 3:
                cout << "Wyszukaj wartosc: ";
                cin >> value;

                startTimer();
                heap->findValue(value);
                endTimer();

                // metoda zwraca indeks elementu jesli nie znajdzie zwroci -1
                if (heap->findValue(value) >= 0) {
                    cout << "Znaleziono" << endl;
                } else {
                    cout << "Nie znaleziono" << endl;
                }
                break;

            case 4:
                startTimer();
                heap->loadNumbers();
                endTimer();
                break;

            case 5: {
                int n;
                cout << "Podaj n: ";
                cin >> n;
                heap->runTests(n);
            } break;

            case 6:
                startTimer();
                heap->clearHeap();
                endTimer();
                break;
        }

        cout << "\nCzas: " << getPerformance() << " ms\n";
        cout << "Enter" << endl;
        cin.get();
        cin.get();
    }

    delete heap;
}

void menuNumbersGenerator() {
    int number;
    int range;

    cout << "Ile liczb wygenerowac: ";
    cin >> number;
    cout << "Podaj gorny zakres liczb do wygenerowania: ";
    cin >> range;

    generator(number, range);

    cout << "Gotowe!" << endl;
    cin.get();
    cin.get();
}

void generator(int length, int range) {
    srand(time(NULL));

    fstream plik;
    plik.open("_sampleNumbers.txt", ios::out);
    plik << length;  // pierwsza linia pliku przechowuje ilosc elementow

    for (int i = 0; i < length; i++) {
        plik << "\n"
             << rand() % range + 1;
    }
    plik.close();
}
