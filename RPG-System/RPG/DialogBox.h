#pragma once

// the actual dialog box.

#include <SFML\Graphics.hpp>
#include "Controller.h"
#include <sstream>
#include <string>

using std::stringstream;
using std::string;

class Controller;

class DialogBox
{
public:
	DialogBox(const string& str, const sf::Color& rect_color = sf::Color::Color(0,160,200,200), const sf::Color& outline_color = sf::Color::White);
	void Update(Controller& ctrl, float elapsedTime);
	void Render(Controller& ctrl);
	void setString(const string& str);
	bool newLine();

private:
	sf::RectangleShape _rect; // background rectangle
	sf::Text _text; // the text

	stringstream _stream;
	stringstream _line;
	string _str;

	float _clock; // measures the time between characters to display
};