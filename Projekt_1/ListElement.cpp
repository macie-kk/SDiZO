#include "ListElement.h"
#include <iostream>

ListElement::ListElement(int value, ListElement *next, ListElement *previous) {
    this->value = value;
    this->next = next;
    this->previous = previous;
}
ListElement::ListElement(int value) : ListElement(value, NULL, NULL) {}
ListElement::ListElement(int value, ListElement *next) : ListElement(value, next, NULL) {}
ListElement::~ListElement() {}
