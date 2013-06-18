#include "DialogBox.h"
#include "Controller.h"
#include <iostream>
#include "Utility.h"
#include "Bank.h"
#include "Macros.h"

// constructor: gets the string to be displayed, and the colored of the outer rectangle
DialogBox::DialogBox(const string& str, const sf::Color& rect_color, const sf::Color& outline_color) : _stream(str), _clock(0.f)
{
	_rect.setFillColor(rect_color);
	_rect.setOutlineColor(outline_color);
	_rect.setOutlineThickness(2.f);

	_text.setFont(Bank<sf::Font>::getInstance().get("resources/consola.ttf"));

	newLine(); // reads the next line
}

// clear everything and set the string
void DialogBox::setString(const string& str)
{
	_line = stringstream(); // clear
	_str.clear();
	_stream = stringstream(str);
	_text.setString(_str); // clear
	newLine();
}

// reads a new line from the stream or returns bool if stream is empty
bool DialogBox::newLine()
{
	_line = stringstream(); // clear
	_str.clear(); // clear
	_text.setString(_str); // clear
	if (_stream.eof())
		return false;
	string temp;
	getline(_stream, temp); // get line from stream
	_line = stringstream(temp); // feed _line

	return true;
}

// read next character
void DialogBox::Update(Controller& ctrl, float elapsedTime)
{
	// updated sizes for text and rect
	sf::Vector2f center = ctrl.getView().getCenter();
	sf::Vector2f size = ctrl.getView().getSize();

	_rect.setSize(sf::Vector2f(size.x/2.5f, size.y/4.f));
	_rect.setPosition(center.x - (_rect.getSize().x/2.f) , center.y + (_rect.getSize().y/2.f));
	_text.setPosition(_rect.getPosition() + PADDING);

	_text.setCharacterSize(unsigned(_rect.getSize().y)/10);
	// -------------------------------

	_clock += elapsedTime;
	if (_clock < 1.f/TEXT_SPEED || _line.eof()) // only allow TEXT_SPEED chars per second
		return;
	_clock = 0.f; // init clock

	char c = _line.get(); // get next char

	// -------- check size of text ------------
	_text.setString(_str + "aaaa"); // extra 4 letters
	string str(_str); // save current

	string temp; // chars to add to current text displayed
	// if _text is bigger than it should
	if (_text.getGlobalBounds().width > _rect.getSize().x - PADDING.x*2)
	{
		// and next char is not space
		if (_str.back() != ' ' && c != ' ')
			if (_line.peek() != ' ') // if next char is not space, write this char and -
			{
				temp += c;
				temp += '-';
			}
			else { temp += c; _line.get(); } // next char is space. so we'll display this and clean the next
		temp += '\n'; // add new line
	}
	if (temp.size() < 2) // if we didn't add it before the -
		temp += c;

	// set last string
	_text.setString(str);
	_str += temp; // set next string
}

void DialogBox::Render(Controller& ctrl)
{

	ctrl.getWindow().draw(_rect);
	ctrl.getWindow().draw(_text);
}