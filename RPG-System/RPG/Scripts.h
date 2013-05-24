#pragma once

#include "Script.h"
#include <vector>

using std::vector;

class Scripts : public Script
{
public:
	Scripts(vector<Script*>& scripts) : _scripts(scripts) { }


private:
	vector<Script*> _scripts;
};
