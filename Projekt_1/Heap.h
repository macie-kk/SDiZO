#include <fstream>
#include <string>

#ifndef HEAP_H
#define HEAP_H

class Heap {
   public:
    int *array;
    int length;

    Heap();
    ~Heap();

    void push(int value);
    void pop(int value);
    int findValue(int value);
    void fixDown(int index);
    void fixUp(int index);
    void show();
    void showRec(const std::string &prefix, int index);
    void loadNumbers();
    void clearHeap();

    void runTests(int amount);
    void testFindVal(std::ofstream &file, int amount);
    void testPop(std::ofstream &file, int amount);
    void testPush(std::ofstream &file, int amount);
};

#endif
