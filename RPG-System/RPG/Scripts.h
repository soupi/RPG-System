#pragma once

// Scripts holds an array of Scripts

#include "Script.h"
#include <vector>

using std::vector;

class Scripts : public Script
{
public:
	Scripts(vector<shared_ptr<Script>>& scripts) : _scripts(scripts) { }

	virtual bool handleEvents(const Control& controls);
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl);

private:
	virtual void enter(Hero& hero);
	virtual void exit();

private:
	vector<shared_ptr<Script>> _scripts;
	unsigned _current;
	Hero* _hero;

	bool Switch();
};
