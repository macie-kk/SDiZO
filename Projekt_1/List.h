#ifndef LIST_H
#define LIST_H

#include <fstream>
#include "ListElement.h"

class List {
   public:
    ListElement *head;
    ListElement *last;
    ListElement *current;
    int length;

    List();
    ~List();

    ListElement *findElement(int value);
    void pushFirst(int value);
    void pushLast(int value);
    void pushIndex(int index, int value);
    void popFirst();
    void popLast();
    void popIndex(int value);
    void popValue(int value);
    void replaceElement(int oldElement, int newElement);
    void searchElement(int value);
    void show();
    void loadNumbers();
    void clearList();

    void runTests(int amount);
    void testFindElement(std::ofstream &file, int amount);
    void testPopFirst(std::ofstream &file, int amount);
    void testPopLast(std::ofstream &file, int amount);
    void testPushFirst(std::ofstream &file, int amount);
    void testPushLast(std::ofstream &file, int amount);
    void testPushIndex(std::ofstream &file, int amount);
    void testReplaceElement(std::ofstream &file, int amount);
};

#endif
