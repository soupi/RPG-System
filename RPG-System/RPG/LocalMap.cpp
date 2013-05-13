#include "LocalMap.h"
#include "Controller.h"


bool LocalMap::Update(Controller& ctrl, float elapsedTime) {
	sf::Event event;
	if (ctrl.getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return true;
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				ctrl.getStateMachine().Stack("gamemenu");
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				_color += 79 % 255;
				_rect.setFillColor(sf::Color::Color(_color, 100, 100));
			}
		}
	}
	return false;
}

void LocalMap::Render(sf::RenderWindow& window)
{
	window.draw(_rect);
}

void LocalMap::init()
{
	_rect.setPosition(0.f,0.f);
	_rect.setSize(sf::Vector2f(800.f, 600.f));
	_rect.setFillColor(sf::Color::Color(0, 100, 100));
}