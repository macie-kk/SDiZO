#include <iostream>
#include "Menu.h"

using namespace std;

int main() {
    int choice = 1;

    while (choice) {
        options();

        cin >> choice;
        switch (choice) {
            case 1:
                menuArray();
                break;
            case 2:
                menuList();
                break;
            case 3:
                menuHeap();
                break;
            case 4:
                menuNumbersGenerator();
                break;
            default:
                break;
        }
    }

    return 0;
}
