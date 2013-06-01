#pragma once
#include <string>

using std::string;

class QuestItem 
{
public:
	QuestItem(const string& name) : _name(name) {}
	const string& name() const { return _name; }

private:
	string _name;
};