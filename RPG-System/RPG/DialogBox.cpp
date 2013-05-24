#include "DialogBox.h"
#include <iostream>

DialogBox::DialogBox(const string& str) : _stream(str) 
{
	_rect.setFillColor(sf::Color::Color(0,160,200,100));
	_rect.setOutlineColor(sf::Color::White);
	_rect.setOutlineThickness(2.f);



	newLine();
}

bool DialogBox::newLine()
{
	_line.clear();
	_str.clear();
	if (_stream.end)
		return false;
	string temp;

	getline(_stream, temp);
	_line << temp;
}

void DialogBox::Update(Controller& ctrl, float elapsedTime)
{
	sf::Vector2f center = ctrl.getView().getCenter();
	sf::Vector2f size = ctrl.getView().getSize();

	_rect.setSize(sf::Vector2f(size.x/2.f, size.y/4.f));
	_rect.setPosition(center.x - (_rect.getSize().x/2.f) , center.y + (_rect.getSize().y/2.f));

	_clock += elapsedTime;
	if (_clock < 1.f/SPEED || _line.end)
		return;

	_clock = 0.f;
	_str += _line.get();
	_text.setString(_str);
}

void DialogBox::Render(sf::RenderWindow& window)
{
	window.draw(_rect);
	window.draw(_text);
}