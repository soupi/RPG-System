#pragma once

#include <map>
#include <string>

using std::string;
using std::map;
using std::pair;

template <class T>
class Bank
{
public:
	static Bank& getInstance()
	{
		static Bank instance;
		return instance;
	}
	const T* get(string& name)
	{
		return _items[name];
	}
private:
	// Private Constructor
	Bank(vector<pair<string, string>>& items) 
	{

		for (auto it = items.begin(); it != items.end(); ++it)
		{
			T item;
			if (!item.loadFromFile(it->second()))
				std::cerr << "fail to load texture from: " << it->second();
			else
				_items.insert(it->first(), item);
		}
	
	}
	// Stop the compiler generating methods of copy the object
	Bank(Bank const& copy) { }           // Not Implemented
	Bank& operator=(Bank const& copy) { } // Not Implemented
	// variables
	map<string, T> _items;
};
