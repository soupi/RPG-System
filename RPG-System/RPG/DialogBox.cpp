#include "DialogBox.h"
#include "Controller.h"
#include <iostream>
#include "Utility.h"



DialogBox::DialogBox(const string& str) : _stream(str), _clock(0.f)
{
	_rect.setFillColor(sf::Color::Color(0,160,200,200));
	_rect.setOutlineColor(sf::Color::White);
	_rect.setOutlineThickness(2.f);

	LoadFont(_font, "resources/consola.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(24);

	newLine();
}

void DialogBox::setString(const string& str)
{
	_line = stringstream();
	_str.clear();
	_stream = stringstream(str);
	_text.setString(_str);
	newLine();
}

bool DialogBox::newLine()
{
	_line = stringstream();
	_str.clear();
	_text.setString(_str);
	if (_stream.eof())
		return false;
	string temp;
	getline(_stream, temp);
	_line = stringstream(temp);

	return true;
}

void DialogBox::Update(Controller& ctrl, float elapsedTime)
{
	_clock += elapsedTime;
	if (_clock < 1.f/SPEED || _line.eof())
		return;
	_clock = 0.f;
	_text.setString(_str);
	_str += _line.get();
	if ((_str.length()-(_str.length() / 40)) % 40 == 0)
	{
		if (_str.back() != ' ')
		{
			if (_line.peek() != ' ')
				_str += '-';
			else _line.get();
		}
		_str += '\n';
	}
}

void DialogBox::Render(Controller& ctrl)
{
	sf::Vector2f center = ctrl.getView().getCenter();
	sf::Vector2f size = ctrl.getView().getSize();

	_rect.setSize(sf::Vector2f(size.x/2.f, size.y/4.f));
	_rect.setPosition(center.x - (_rect.getSize().x/1.5f) , center.y + (_rect.getSize().y/2.f));
	_text.setPosition(_rect.getPosition() + sf::Vector2f(20.f, 20.f));

	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_text);
}