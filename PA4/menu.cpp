#include "menu.h"
#include <fstream>
#include <sstream>
#include <iostream>

// determines if command is valid 
bool validCommand(string line)
{
	return (line.rfind("find", 0) == 0) || (line.rfind("listInventory", 0) == 0);
}

// read the command inputted by user and determines which function to call
void readCommand(string line, HashTable& inventory, CategoryList& categoryList)
{
	if (line.rfind("find", 0) == 0)
	{
		string inventoryId = line.substr(5);  // find ______
		cout << '\n';
		find(inventoryId, inventory);
	}
	else if (line.rfind("listInventory", 0) == 0)
	{
		string category = line.substr(13); // listInventory _______
		cout << '\n';
		listInventory(category, categoryList);
	}
	else
	{
		cout << "Unknown command." << endl;
	}
}

// load and parse csv, populate lists
void loadCSV(const string& filename, HashTable& inventory, CategoryList& categoryList) 
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cerr << "Error, unable to open file." << endl;
		return;
	}

	string line;
	getline(file, line); // skip header line

	while (getline(file, line))
	{
		if (line.empty()) // if line empty, skip
		{
			continue;
		}

		stringstream ss(line);
		Product prod;
		string categoriesUnsplit;

		getline(ss, line, ','); // uniqId
		prod.setUniqId(line);  

		line.clear(); // product name
		char ch;
		if (ss.get(ch) && ch == '"')  // handle names surrounded by quotes
		{
			while (ss.get(ch))
			{
				if (ch == '"')  // check for closing quote
				{
					if (ss.peek() == '"')  // check if next character is quote
					{
						line.push_back(ch); 
						ss.get(ch); 
					}
					else
					{
						break;  // end of quoted field
					}
				}
				else
				{
					line.push_back(ch);  // add character to the field
				}
			}
			prod.setName(line);
			getline(ss, line, ',');
		}
		else
		{
			ss.putback(ch);  // unquoted name field
			getline(ss, line, ',');  
			prod.setName(line); 
		}

		// skip to category
		getline(ss, line, ',');
		getline(ss, line, ',');

		// categories
		if (ss.get(ch) && ch == '"') // check if surrounded by quotes
		{
			line.clear();
			while (ss.get(ch))
			{
				if (ch == '"') 
				{
					if (ss.peek() == '"')  
					{
						line.push_back(ch);
						ss.get(ch);
					}
					else
					{
						break;
					}
				}
				else
				{
					line.push_back(ch); 
				}
			}
		}
		else
		{
			ss.putback(ch);
			getline(ss, line, ',');
		}
		categoriesUnsplit = trim(line);

		// handle missing or empty categories
		vector<string> cats = splitCategories(categoriesUnsplit, '|');
		if (cats.empty())
		{
			cats.push_back("NA");  // if no category, NA
		}

		// adding the product to the category list
		for (auto& category : cats)
		{
			categoryList.addProduct(category, prod);
		}

		// Inserting the product into the HashTable (using uniqId as the key)
		inventory.insert(prod);
	}

	file.close();
}

// plays when program is opened, shows menu
void bootStrap(HashTable& inventory, CategoryList& categoryList) 
{
	cout << "Amazon REPL inventory system." << endl;

	// Load the inventory from CSV file
	loadCSV("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data (1).csv", inventory, categoryList);

	cout << "\nInventory loaded successfully." << endl;
	cout << " \n---Commands---\n1. find <inventoryid>" << endl;
	cout << "2. listInventory <category_string>\n";
	cout << "3. exit to end program\n";
}

// split the categories by a delimiter (|)
vector<string> splitCategories(const string& s, char delimiter)
{
	vector<string> cats;
	stringstream ss(s);
	string cat;
	while (getline(ss, cat, delimiter))
	{
		cat = trim(cat);  // trim to avoid whitespaces
		if (!cat.empty())  // only add non empty categories
		{
			cats.push_back(cat);
		}
	}
	return cats;
}

// find a product by uniqId
void find(const string& inventoryId, HashTable& inventory)
{
	Product* prod = inventory.search(inventoryId);
	if (prod)
	{
		cout << "Product Found: \n" << *prod << endl;
	}
	else
	{
		cout << "Product not found." << endl;
	}
}

// print a list of products within a category
void listInventory(const string& category, CategoryList& categoryList) 
{
	string trimmedCategory = trim(category);
	categoryList.findProducts(trimmedCategory);
}

// trim whitespaces that occur on categories
string trim(const string& str)
{
	size_t start = str.find_first_not_of(" \t\n\r");
	if (start == string::npos)
	{
		return "";  // if only spaces, return empty 
	}
	size_t end = str.find_last_not_of(" \t\n\r");
	return str.substr(start, end - start + 1);
}
