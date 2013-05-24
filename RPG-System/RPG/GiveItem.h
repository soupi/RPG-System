#pragma once

#include "Script.h"
#include <string>

using std::string;

class GiveItem : public Script
{
public:
	GiveItem(const string& item_name) : _item(item_name) { }

private:
	string _item;
};