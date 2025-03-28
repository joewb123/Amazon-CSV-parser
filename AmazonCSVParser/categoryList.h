#ifndef CATEGORYLIST_H_
#define CATEGORYLIST_H_

#include <string>
#include <vector>
#include "Product.h"

class CategoryList
{
private:
    struct Node
    {
        string category;
        vector<Product> products;
        Node* pNext;

        Node(const string& cat) : category(cat), pNext(nullptr) {}
    };

    Node* head;

public:
    CategoryList() : head(nullptr) {}

    // add a product into a category
    void addProduct(const string& category, const Product& product)
    {
        Node* pCur = head;
        Node* pPrev = nullptr;

        // find category in the list
        while (pCur != nullptr)
        {
            if (pCur->category == category)
            {
                pCur->products.push_back(product); // add product
                return;
            }
            pPrev = pCur;
            pCur = pCur->pNext;
        }

        // category wasn't found
        Node* newNode = new Node(category);
        newNode->products.push_back(product);

        if (pPrev == nullptr) // insert at head if the only category
        {
            head = newNode;
        }
        else
        {
            pPrev->pNext = newNode;
        }
    }

    // lists all uniq id and product name for each product in a category
    void findProducts(const string& category)
    {
        Node* pCur = head;

        // find the category within the list of categories
        while (pCur != nullptr)
        {
            if (pCur->category == category)
            {
                // print details of all products found in category
                for (const auto& product : pCur->products)
                {
                    cout << product;
                }
                return;
            }
            pCur = pCur->pNext;
        }
        cout << "Category not found.\n";
    }





    // Prints all categories and their products
    void printCategories() const
    {
        Node* pCur = head;
        while (pCur != nullptr)
        {
            cout << "Category: " << pCur->category << ", Products: " << pCur->products.size() << endl;
            pCur = pCur->pNext;
        }
    }

    // destructor
    ~CategoryList()
    {
        Node* pCur = head;
        while (pCur != nullptr)
        {
            Node* temp = pCur;
            pCur = pCur->pNext;
            delete temp;
        }
    }
};

#endif
