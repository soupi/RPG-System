#pragma once

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
	DialogBox(const string& str);
	void Update(Controller& ctrl, float elapsedTime);
	void Render(Controller& ctrl);
	void setString(const string& str);
//	void setPos(const sf::Vector2f& pos);
//	void setSize(const sf::Vector2u& size);
	bool newLine();

private:
	sf::RectangleShape _rect;
	sf::Text _text;
	stringstream _stream;
	stringstream _line;
	string _str;
	float _clock;
};