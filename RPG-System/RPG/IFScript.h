#pragma once

#include "Script.h"
#include "HeroCharacter.h"
#include "NoScript.h"

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
	virtual bool check(Hero& hero) = 0;
};

class IFLevel : public IFScript
{
public:
	IFLevel(unsigned level, shared_ptr<Script>& if_s, shared_ptr<Script>& else_s = shared_ptr<Script>(new NoScript)) : IFScript(if_s, else_s), _level(level) { }
	virtual bool check(Hero& hero);
private:
	unsigned _level;
};

using std::string;

class IFQItem : public IFScript
{
public:
	IFQItem(const string& item_name, shared_ptr<Script>& if_s, shared_ptr<Script>& else_s = shared_ptr<Script>(new NoScript)) : IFScript(if_s, else_s), _item_name(item_name) { }
	virtual bool check(Hero& hero);
private:
	string _item_name;
};