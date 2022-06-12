#pragma once

using namespace std;

#include <string>

class Table {
   private:
    int* tab;
    int cnt;  // ilo�� element�w w tablicy

    void destroyTable();

   public:
    Table();
    ~Table();

    void loadFromFile(string FileName);

    bool IsValueInTable(int val);

    void AddFront(int val);

    void AddBack(int val);

    void AddRandom(int val);

    void AddAtIndex(int val, int index);

    void deleteFromTable(int index);

    void display();

    void generateTable(int size);
};