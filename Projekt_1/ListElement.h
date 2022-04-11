#ifndef LISTELEMENT_H
#define LISTELEMENT_H

class ListElement {
   public:
    ListElement *next;
    ListElement *previous;
    int value;

    ListElement(int, ListElement *, ListElement *);
    ListElement(int, ListElement *);
    ListElement(int);
    ~ListElement();
};

#endif
