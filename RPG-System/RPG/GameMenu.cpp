#include "GameMenu.h"
#include "Controller.h"

bool GameMenu::Update(Controller& ctrl, float elapsedTime) {
	sf::Event event;
	if (ctrl.getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return true;
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				ctrl.getStateMachine().Pop();
			else if (event.mouseButton.button == sf::Mouse::Button::Right)
			{
				_color += 79 % 255;
				_rect.setFillColor(sf::Color::Color(100, 100, _color));
			}
		}
	}
	return false;
}

void GameMenu::Render(sf::RenderWindow& window)
{
	window.draw(_rect);
}

void GameMenu::init()
{
	_rect.setPosition(0.f,0.f);
	_rect.setSize(sf::Vector2f(800.f, 600.f));
	_rect.setFillColor(sf::Color::Yellow);
}