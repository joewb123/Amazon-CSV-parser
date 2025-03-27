#include "hashtable.h"
#include <iostream>

using namespace std;

HashTable::HashTable()
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        table[i] = nullptr; // Initialize all table slots to nullptr
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        Node* pCur = table[i];
        while (pCur != nullptr) 
        {
            Node* temp = pCur;
            pCur = pCur->pNext;
            delete temp;
        }
    }
}

int HashTable::hashFunction(const string& key)
{
    int hash = 0;
    for (char ch : key) 
    {
        hash = (hash * 31 + ch) % HASH_SIZE; // prime number 31
    }
    return hash;
}

// insert product into the hash table
void HashTable::insert(Product& prod)
{
    int index = hashFunction(prod.getUniqId()); // get the index from the hash function
    Node* newNode = new Node(prod);

    if (table[index] == nullptr)
    {
        table[index] = newNode; // if no collision, directly insert
    }
    else
    {
        Node* pCur = table[index];
        while (pCur->pNext != nullptr)
        {
            pCur = pCur->pNext;
        }
        pCur->pNext = newNode; // if collision, add to the end
    }
}

// search hashtable by uniqId
Product* HashTable::search(const string& uniqId)
{
    int index = hashFunction(uniqId);
    Node* pCur = table[index];
    while (pCur != nullptr) 
    {
        if (pCur->prod.getUniqId() == uniqId)
        {
            return &(pCur->prod); // found, return pointer
        }
        pCur = pCur->pNext;
    }
    return nullptr; // not found
}

