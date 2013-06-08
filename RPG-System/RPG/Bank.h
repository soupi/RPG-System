#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>

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
	const T& get(string filename)
	{
		// if exists, return it.
		if (_items.find(filename) != _items.end())
			return _items[filename];

		T item;
		if (!item.loadFromFile(filename))
			std::cerr << "fail to load item from: " << filename;
		else
			_items[filename] = item;
		return _items[filename];
	}
private:
	// Private Constructor
	Bank(std::vector<string>& items) 
	{
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			get(*it);
		}
	}
	Bank() { }
	// Stop the compiler generating methods of copy the object
	Bank(Bank const& copy) { }           // Not Implemented
	Bank& operator=(Bank const& copy) { } // Not Implemented
	// variables
	map<string, T> _items;
};