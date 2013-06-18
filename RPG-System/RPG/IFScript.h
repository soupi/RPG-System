#pragma once

// IF Scripts

#include "Script.h"
#include "HeroCharacter.h"
#include "NoScript.h"

// base class for other IF scripts. will decide which script to run based on an if statement
class IFScript : public Script
{
public:
	IFScript(shared_ptr<Script>& if_s, shared_ptr<Script>& else_s) : _check(false), _if_script(if_s), _else_script(else_s) { }
	virtual ~IFScript() { }
	virtual bool handleEvents(const Control& controls);
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl);

protected:
	shared_ptr<Script> _if_script;
	shared_ptr<Script> _else_script;
	bool _if, _check;

private:
	virtual void enter(Hero& hero);
	virtual void exit();
	virtual bool check(Hero& hero) = 0; // this should be implemented by derived classes
};

// if the hero's level is _level or above, activate if_script. else, activate else_script
class IFLevel : public IFScript
{
public:
	IFLevel(unsigned level, shared_ptr<Script>& if_s, shared_ptr<Script>& else_s = shared_ptr<Script>(new NoScript)) : IFScript(if_s, else_s), _level(level) { }
private:
	unsigned _level;
	virtual bool check(Hero& hero);
};

using std::string;

// if the hero has _item_name activate if_script. else, activate else_script
class IFQItem : public IFScript
{
public:
	IFQItem(const string& item_name, shared_ptr<Script>& if_s, shared_ptr<Script>& else_s = shared_ptr<Script>(new NoScript)) : IFScript(if_s, else_s), _item_name(item_name) { }

private:
	string _item_name;
	virtual bool check(Hero& hero);
};