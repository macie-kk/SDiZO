#ifndef Array_H
#define Array_H

#include <fstream>

class Array {
   public:
    int *array;
    int length;

    Array();
    ~Array();

    void pushIndex(int index, int value);
    void pushFirst(int value);
    void pushLast(int value);
    void popFirst();
    void popLast();
    void popIndex(int index);
    void popValue(int value);
    int findElement(int value);
    void replaceElement(int oldValue, int newValue);
    void show();
    void loadNumbers();
    void clearArray();

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
