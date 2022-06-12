#pragma once

template <typename T>
class ElemList {
   private:
    T data;
    ElemList* next;
    ElemList* prev;

   public:
    ElemList(T& data);

    // gettery
    T& getData();
    ElemList* getPrev();
    ElemList* getNext();

    // settery
    void setData(T data);
    void setPrev(ElemList* prev);
    void setNext(ElemList* next);

    void insert(ElemList* elem);

    void remove();

    T display();
};

template <typename T>
ElemList<T>::ElemList(T& data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

template <typename T>
T& ElemList<T>::getData() {
    return this->data;
}

template <typename T>
void ElemList<T>::setData(T data) {
    this->data = data;
}

template <typename T>
ElemList<T>* ElemList<T>::getPrev() {
    return this->prev;
}

template <typename T>
ElemList<T>* ElemList<T>::getNext() {
    return this->next;
}

template <typename T>
void ElemList<T>::setPrev(ElemList* prev) {
    this->prev = prev;
}

template <typename T>
void ElemList<T>::setNext(ElemList* next) {
    this->next = next;
}

template <typename T>
void ElemList<T>::insert(ElemList* elem) {
    elem->setNext(this);
    elem->setPrev(this->getPrev());

    if (this->getPrev() != nullptr)
        this->getPrev()->setNext(elem);

    this->setPrev(elem);
}

template <typename T>
T ElemList<T>::display() {
    return data;
}

template <typename T>
void ElemList<T>::remove() {
    if (this->getNext() != nullptr)
        this->getNext()->setPrev(this->getPrev());

    if (this->getPrev() != nullptr)
        this->getPrev()->setNext(this->getNext());
}