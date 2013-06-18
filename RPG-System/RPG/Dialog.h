#pragma once

// Script to display a dialog

#include "Script.h"
#include "DialogBox.h"
#include <string>

using std::string;

class Dialog : public Script 
{
public:
	Dialog(const string& str, const sf::Color& rect_color = sf::Color::Color(0,160,200,200), const sf::Color& outline_color = sf::Color::White);
	virtual bool handleEvents(const Control& controls);
	virtual bool Update(Controller&, float elapsedTime);
	virtual void Render(Controller& ctrl);
private:
	DialogBox _dialogbox;
	string _str;

	virtual void enter(Hero& hero);
	virtual void exit();
};


