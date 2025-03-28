#ifndef MENU_H_
#define MENU_H_

#include <vector>
#include <string>
#include "hashtable.h"
#include "Product.h"
#include "categoryList.h"

using namespace std;

class Product;
class HashTable;

void bootStrap(HashTable& inventory, CategoryList& categoryList);
void loadCSV(const string& filename, HashTable& inventory, CategoryList& categoryList);
bool validCommand(string line);
void readCommand(string line, HashTable& inventory, CategoryList& categoryList);
vector<string> splitCategories(const string& s, char delimiter);
void find(const string& inventoryId, HashTable& inventory);
void listInventory(const string& category, CategoryList& categoryList);
string trim(const string& str);

#endif
