#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "Product.h"

using namespace std;

class HashTable
{
private:
    static const int HASH_SIZE = 10003; // Large prime number

    struct Node
    {
        Product prod;
        Node* pNext;

        Node(Product p) : prod(p), pNext(nullptr) {} // constructor
    };

    Node* table[HASH_SIZE]; // array of pointers

public:
    HashTable();                // constructor
    ~HashTable();               // destructor
    int hashFunction(const string& key);
    void insert(Product& prod);  // insert product into the hash table
    Product* search(const string& uniqId); // search product by uniqId

};

#endif
