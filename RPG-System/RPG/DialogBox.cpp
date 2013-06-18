#include "DialogBox.h"
#include "Controller.h"
#include <iostream>
#include "Utility.h"
#include "Bank.h"

const sf::Vector2f PADDING = sf::Vector2f(20.f, 20.f);

DialogBox::DialogBox(const string& str, const sf::Color& rect_color, const sf::Color& outline_color) : _stream(str), _clock(0.f)
{
	_rect.setFillColor(rect_color);
	_rect.setOutlineColor(outline_color);
	_rect.setOutlineThickness(2.f);

	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));

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
	// updated sizes for text and rect
	sf::Vector2f center = ctrl.getView().getCenter();
	sf::Vector2f size = ctrl.getView().getSize();

	_rect.setSize(sf::Vector2f(size.x/2.5f, size.y/4.f));
	_rect.setPosition(center.x - (_rect.getSize().x/2.f) , center.y + (_rect.getSize().y/2.f));
	_text.setPosition(_rect.getPosition() + sf::Vector2f(20.f, 20.f));

	_text.setCharacterSize(unsigned(_rect.getSize().y)/10);
	// -------------------------------

	_clock += elapsedTime;
	if (_clock < 1.f/TEXT_SPEED || _line.eof())
		return;
	_clock = 0.f;

	char c = _line.get();
	_text.setString(_str + c + c + c);
	string str(_str);

	string temp;

	if (_text.getGlobalBounds().width > _rect.getSize().x - PADDING.x*2)
	{
		if (_str.back() != ' ' && c != ' ')
			if (_line.peek() != ' ')
				temp += '-';
			else { temp += c; _line.get(); } // next char is space.
		temp += '\n';
	}
	if (temp.size() < 2)
		temp += c;

	_text.setString(str);
	_str += temp;
}

void DialogBox::Render(Controller& ctrl)
{

	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_text);
}