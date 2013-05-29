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
	virtual void Exit();
private:
	DialogBox _dialogbox;
	string _str;
	float _clock;

	virtual void enter(Hero& hero);
};


