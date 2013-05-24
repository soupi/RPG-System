#pragma once

#include "Script.h"
#include "DialogBox.h"
#include <string>

using std::string;

class Dialog : public Script 
{
public:
	Dialog(string& str);
	virtual void Enter(Hero& hero);
	virtual bool handleEvents(const Control& controls);
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl);
	virtual void Exit();

private:
	DialogBox _dialogbox;
};


