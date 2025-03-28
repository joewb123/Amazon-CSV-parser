#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product
{
private:
    string uniqId;
    string name;
    vector<string> categories;

public:
    // default constructor
    Product() : uniqId(""), name(""), categories(1, "NA") {}

    // parameterized constructor
    Product(const string& id, const string& name)
        : uniqId(id), name(name), categories() {}

    // getters
    string getUniqId() const 
    { 
        return uniqId; 
    }
    string getName() const 
    { 
        return name; 
    }
    vector<string> getCategories() const 
    {
        return categories; 
    }

    // setters
    void setUniqId(const string& id) 
    { 
        uniqId = id; 
    }
    void setName(const string& n) 
    {
        name = n; 
    }
    void setCategories(const vector<string>& c) 
    { 
        categories = c; 
    }

    // overloaded output operator for outputting products
    friend ostream& operator<<(ostream& o, const Product& p)
    {
        o << p.name << "\nProduct ID: " << p.uniqId << "\n\n";
        return o;
    }
};

#endif
