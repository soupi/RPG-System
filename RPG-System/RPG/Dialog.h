#pragma once

#include "Script.h"
#include "DialogBox.h"
#include <string>

using std::string;

class Dialog : public Script 
{
public:
	Dialog(const string& str);
	virtual bool handleEvents(const Control& controls);
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl);
private:
	DialogBox _dialogbox;
	string _str;

	virtual void enter(Hero& hero);
	virtual void exit();
};


