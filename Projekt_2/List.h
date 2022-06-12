#pragma once
#include <iostream>
#include <string>
#include "ElemList.h"

using namespace std;

template <typename T>
class List {
   private:
    ElemList<T>* head;
    ElemList<T>* tail;

    ElemList<T>* insert(int index, T value);
    void destroyList();

   public:
    List();
    ~List();

    void AddBack(T value);

    ElemList<T>* getElement(int index) const;

    void display();

    int size();

    // przeciążanie operatorów
    T& operator[](int index) {
        return getElement(index)->getData();
    }
};

template <typename T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
}

template <typename T>
void List<T>::destroyList() {
    ElemList<T>* elem = head;
    ElemList<T>* next_elem = nullptr;

    if (elem != nullptr)
        next_elem = elem->getNext();

    while (elem != nullptr) {
        delete elem;

        elem = next_elem;

        if (elem != nullptr)
            next_elem = elem->getNext();
    }

    head = nullptr;
    tail = nullptr;
}

template <typename T>
void List<T>::AddBack(T value) {
    this->insert((this->size() - 1), value);
}

template <typename T>
ElemList<T>* List<T>::insert(int index, T value) {
    ElemList<T>* new_elem = new ElemList<T>(value);

    if (index == (this->size() - 1) && tail != nullptr) {
        tail->setNext(new_elem);
        new_elem->setPrev(tail);

        tail = new_elem;
        return new_elem;
    }

    ElemList<T>* elem = getElement(index);

    if (elem != nullptr)
        elem->insert(new_elem);

    if (new_elem->getPrev() == nullptr)
        head = new_elem;

    if (new_elem->getNext() == nullptr)
        tail = new_elem;

    return new_elem;
}

template <typename T>
ElemList<T>* List<T>::getElement(int index) const {
    ElemList<T>* elem = head;

    while (index > 0 && elem != nullptr) {
        elem = elem->getNext();
        index--;
    }

    return elem;
}

template <typename T>
void List<T>::display() {
    ElemList<T>* elem = head;

    cout << "front: ";

    while (elem != nullptr) {
        cout << elem->display() << " ";
        elem = elem->getNext();
    }

    cout << "\nback: ";
    elem = tail;

    while (elem != nullptr) {
        cout << elem->display() << " ";
        elem = elem->getPrev();
    }

    cout << endl
         << endl;
}

template <typename T>
int List<T>::size() {
    ElemList<T>* elem = head;
    int len = 0;

    while (elem != nullptr) {
        elem = elem->getNext();
        len++;
    }

    return len;
}

template <typename T>
List<T>::~List() {
    destroyList();
}