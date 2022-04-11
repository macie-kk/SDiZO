#include "List.h"
#include <algorithm>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "ListElement.h"
#include "Menu.h"
using namespace std;

List::List() {
    head = NULL;     // zresetowanie pierwszego elementu
    current = NULL;  // zresetowanie zmiennej do wyszukiwania
    last = NULL;
    length = 0;  // zresetowanie dlugosci listy
}

List::~List() {
    for (int i = 0; i < length; i++) {
        current = head->next;
        delete head;
        head = current;
    }
}

void List::pushFirst(int value) {
    length++;

    // sprawdzenie czy pierwszy element jest rowny NULL
    if (head == NULL) {
        head = new ListElement(value);  // utworzenie nowego elementu na miejscu pierwszego
        last = head;
        return;
    }

    current = head;                          // przechowanie glowy
    head = new ListElement(value, current);  // ustawienie w miejscu glowy nowego elementu
    current->previous = head;
}

void List::pushLast(int value) {
    length++;

    // sprawdzenie czy pierwszy element jest rowny NULL
    if (head == NULL) {
        last = new ListElement(value);  // utworzenie nowego elementu na miejscu pierwszego
        head = last;
        return;
    }

    current = last;  // ustawienie ostatniego elementu jako obecny
    last = new ListElement(value, NULL, current);
    current->next = last;  // utworzenie nowego elementu na koncu listy i zapisaniego jako obecny
}

void List::pushIndex(int value, int index) {
    current = head;
    ListElement *prev;

    // sprawdzenie czy podany indeks jest poprawny, pozwalajac na dodanie na koniec i poczatek
    if (index > length || index < 0) {
        cout << "Indeks niepoprawny" << endl;
        return;
    }

    if (index == 0) {
        pushFirst(value);  // dodanie na poczatek
        return;
    }

    if (index == length) {
        pushLast(value);  // dodanie na koniec
        return;
    }

    // dodawanie w srodku listy
    for (int i = 0; i < index; i++) {
        prev = current;           // ustawienie poprzedniego na element poprzedzajacy podany indeks
        current = current->next;  // ustawienie obecnego na element znajdujacy sie na podanym indeksie
    }

    ListElement *newElement = new ListElement(value, current, current->next);  // utworzenie nowego elementu
    prev->next = newElement;                                                   // ustawienie poprzedniego elementu zeby wskazywal na nowy
    length++;
}

void List::popFirst() {
    if (head == NULL) {
        cout << "Lista jest pusta" << endl;
        return;
    }

    current = head->next;  // przechowanie nowej glowy
    delete head;           // usuniecie starej glowy
    if (length > 1) {
        current->previous = NULL;
        head = current;
    } else {
        current = NULL;
        head = NULL;
        last = NULL;
    }
    length--;
}

void List::popLast() {
    if (head == NULL) {
        cout << "Lista jest pusta" << endl;
        return;
    }

    current = last->previous;
    delete last;

    if (length > 1) {
        current->next = NULL;
        last = current;
    } else {
        current = NULL;
        head = NULL;
        last = NULL;
    }
    length--;
}

void List::popIndex(int index) {
    // sprawdzenie czy podany indeks nie wykracza poza dlugosc listy
    if (index >= length || index < 0) {
        cout << "Indeks niepoprawny" << endl;
        return;
    }

    // usuniecie pierwszego elementu
    if (index == 0) {
        popFirst();
        return;
    }

    // usuniecie ostatniego elementu
    if (index == length - 1) {
        popLast();
        return;
    }

    // usuniecie elementu ze srodka
    ListElement *temp = head;  // tymczasowy wskaznik

    for (int i = 0; i < index; i++) {
        current = temp;     // ustawienie current na poprzedni element niz wskazany ideksem
        temp = temp->next;  // ustawienie temp na element ze wskazanym indeksem
    }

    // przepisanie nastepnego elementu temp na current
    current->next = temp->next == NULL ? NULL : temp->next;
    delete temp;
    length--;
}

void List::popValue(int value) {
    ListElement *temp = findElement(value);
    ListElement *prev;
    ListElement *pnext;

    if (temp == NULL) {
        cout << "Nie ma takiego elementu" << endl;
        return;
    }

    if (temp == head) {
        popFirst();
        return;
    }

    current = head;
    while (current->value != temp->value) {
        // wyszukanie elementu o podanej wartosci i ustawienie go jako current
        prev = current;
        current = current->next;
    }

    pnext = current->next;
    prev->next = pnext;
    current = NULL;

    delete temp;
    length--;
}

ListElement *List::findElement(int value) {
    current = head;
    while (current != NULL) {
        // jesli wartosc elementu jest rowna podanej zwroc wskaznik na ten element
        if (current->value == value) {
            return current;
        }
        current = current->next;  // przesuniecie obecnego elementu na nastepny
    }
    return NULL;  // jesli nie znaleziono zwroc NULL
}

// metoda findElement wyswietlajaca informacje na ekranie
void List::searchElement(int value) {
    current = head;
    while (current != NULL) {
        // jesli wartosc elementu jest rowna podanej zwroc wskaznik na ten element
        if (current->value == value) {
            cout << "Znaleziono" << endl;
            return;
        }
        current = current->next;  // przesuniecie obecnego elementu na nastepny
    }
    cout << "Nie znaleziono" << endl;
}

void List::replaceElement(int oldValue, int newValue) {
    ListElement *oldElement = findElement(oldValue);
    if (oldElement == NULL) {
        cout << "Nie znaleziono elementu\n";
        return;
    }
    current = oldElement;       // podstawienie za current elementu o wartosci oldValue
    current->value = newValue;  // zmiana wartosci
}

void List::show() {
    current = head;
    cout << "Lista : [";
    while (current != NULL) {
        cout << current->value;  // wyswietlenie wartosci obecnego elementu
        if (current->next != NULL) {
            cout << ", ";
        }
        current = current->next;  // przesuniecie obecnego elementu na nastepny
    }
    cout << "] \nIlosc elementow: " << length << endl;  // wyswietlenie dlugosci tablicy
}

void List::loadNumbers() {
    clearList();

    int amount;
    int value;

    fstream plik;
    plik.open("_sampleNumbers.txt", ios::in);
    plik >> amount;

    for (int i = 0; i < amount; i++) {
        plik >> value;
        pushLast(value);
    }
    plik.close();
}

void List::clearList() {
    while (head != NULL) {
        popFirst();
    }
}

void List::testReplaceElement(std::ofstream &file, int amount) {
    clearList();
    srand(time(NULL));
    int elements[amount];

    file << "Zamien; ";
    for (int i = 1; i <= amount; i++) {
        int newVal = rand() % 100;
        elements[i - 1] = newVal;
        pushFirst(newVal);

        cout << "\rTesting Replace: " << i;
        startTimer();
        replaceElement(elements[rand() % i], rand() % 100);
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

void List::testFindElement(std::ofstream &file, int amount) {
    clearList();
    srand(time(NULL));
    int elements[amount];

    file << "Wyszukaj; ";
    for (int i = 1; i <= amount; i++) {
        int newVal = rand() % 100;
        elements[i - 1] = newVal;
        pushFirst(newVal);

        cout << "\rTesting Find: " << i;
        startTimer();
        findElement(elements[rand() % i]);
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

void List::testPopFirst(std::ofstream &file, int amount) {
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

void List::testPopLast(std::ofstream &file, int amount) {
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

void List::testPushLast(std::ofstream &file, int amount) {
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

void List::testPushFirst(std::ofstream &file, int amount) {
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

void List::testPushIndex(std::ofstream &file, int amount) {
    clearList();
    srand(time(NULL));

    file << "Push Index; ";
    for (int i = 1; i <= amount; i++) {
        cout << "\rTesting push index: " << i;
        if (i == 1) {
            pushFirst(96);
            continue;
        }
        startTimer();
        pushIndex(69, rand() % length);
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

void List::runTests(int amount) {
    filesystem::create_directory("./tests");
    std::ofstream fileOut;
    fileOut.open("./tests/ListTest.csv", std::ios_base::app);

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
    testPushIndex(fileOut, amount);
    testFindElement(fileOut, amount);
    testReplaceElement(fileOut, amount);
    fileOut.close();
    clearList();
}
