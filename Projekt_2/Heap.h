#pragma once

#include <math.h>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Heap {
   private:
    T* arr;
    int size;
    int len;

    bool isFull();
    bool isValidIndex(int index);

    int getLeftChild(int parentIndex);
    int getRightChild(int parentIndex);
    int getParent(int childIndex);

    void resize(int newSize);
    void swapElements(int index1, int index2);

    void minHeapifyUp(int index);
    void minHeapifyDown(int parentIndex);

    void init(int size);
    void destroyHeap();

   public:
    Heap(int size);
    ~Heap();

    void insert(T value);
    void deleteElement(int index);
    bool isValueInHeap(T value);

    void display();

    int getLength();
    T getTop();

    bool isEmpty();

    void clear();
};

// DEFINICJE FUNKCJI
template <typename T>
Heap<T>::Heap(int size) {
    init(size);
}

template <typename T>
void Heap<T>::insert(T value) {
    if (isFull()) {
        this->resize(this->size + 10);
    }

    arr[len] = value;   // przypisanie nowej wartości na koniec tablicy
    minHeapifyUp(len);  // uporządkowanie (przwrócenie własności) kopca
    len++;              // zwiększenie licznika elementów
}

template <typename T>
void Heap<T>::resize(int newSize) {
    T* tmp_arr = new T[newSize];

    for (int i = 0; this->len > i; i++) {
        tmp_arr[i] = arr[i];
    }

    delete[] arr;

    arr = tmp_arr;
    this->size = newSize;
}

template <typename T>
void Heap<T>::swapElements(int index1, int index2) {
    if (index1 == index2)
        return;

    T tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}

template <typename T>
void Heap<T>::minHeapifyUp(int index) {
    int parentIndex = getParent(index);

    while (isValidIndex(parentIndex) && *(arr[index]) < *(arr[parentIndex])) {
        swapElements(index, parentIndex);
        index = parentIndex;
        parentIndex = getParent(index);
    }
}

template <typename T>
void Heap<T>::minHeapifyDown(int parentIndex) {
    int leftChildIndex = getLeftChild(parentIndex);
    int rightChildIndex;
    int smallerValueIndex;

    while (isValidIndex(leftChildIndex)) {
        smallerValueIndex = leftChildIndex;

        rightChildIndex = getRightChild(parentIndex);

        if (isValidIndex(rightChildIndex) && *(arr[rightChildIndex]) < *(arr[leftChildIndex])) {
            smallerValueIndex = rightChildIndex;
        }

        if (*(arr[smallerValueIndex]) < *(arr[parentIndex])) {
            swapElements(smallerValueIndex, parentIndex);
            parentIndex = smallerValueIndex;
            leftChildIndex = getLeftChild(parentIndex);
        } else
            break;
    }
}

template <typename T>
int Heap<T>::getLeftChild(int parentIndex) {
    return (2 * parentIndex) + 1;
}

template <typename T>
int Heap<T>::getRightChild(int parentIndex) {
    return (2 * parentIndex) + 2;
}

template <typename T>
int Heap<T>::getParent(int childIndex) {
    return floor((childIndex - 1) / 2);
}

template <typename T>
bool Heap<T>::isFull() {
    return len >= size;
}

template <typename T>
bool Heap<T>::isEmpty() {
    return len <= 0;
}

template <typename T>
bool Heap<T>::isValidIndex(int index) {
    return (index >= 0 && index < len);
}

template <typename T>
void Heap<T>::display() {
    cout << "---DISPLAY---" << endl;
    for (int i = 0; len > i; i++) {
        cout << i << ". " << arr[i] << "\nval: " << *(arr[i]) << endl;
    }

    cout << endl
         << endl;
}

template <typename T>
void Heap<T>::deleteElement(int index) {
    if (!isValidIndex(index))
        return;
    swapElements(index, len - 1);
    len--;
    minHeapifyDown(0);

    for (int i = len - 1; i > 0; i--)
        minHeapifyUp(i);
}

template <typename T>
void Heap<T>::destroyHeap() {
    if (arr != nullptr)
        delete[] arr;

    arr = nullptr;
    len = 0;
    size = 0;
}

template <typename T>
void Heap<T>::init(int size) {
    this->arr = new T[size];
    this->size = size;
    this->len = 0;
}

template <typename T>
Heap<T>::~Heap() {
    destroyHeap();
}

template <typename T>
int Heap<T>::getLength() {
    return this->len;
}

template <typename T>
T Heap<T>::getTop() {
    return arr[0];
}

template <typename T>
void Heap<T>::clear() {
    this->len = 0;
}

template <typename T>
bool Heap<T>::isValueInHeap(T value) {
    for (int i = 0; len > i; i++) {
        if (arr[i] == value)
            return true;
    }

    return false;
}
