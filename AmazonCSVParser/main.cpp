#include "menu.h"
#include "categoryList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    HashTable inventory;
    CategoryList categoryList;
    string line;
    bootStrap(inventory, categoryList);

    while (getline(cin, line) && line != "exit")
    {
        if (validCommand(line))
        {
            readCommand(line, inventory, categoryList);
        }
        else
        {
            cout << "Retype command (find or listInventory)" << endl;
        }
        cout << "> ";
    }

    return 0;
}
