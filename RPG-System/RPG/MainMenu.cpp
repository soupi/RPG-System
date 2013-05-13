#include "MainMenu.h"
#include "Controller.h"

bool MainMenu::Update(Controller& ctrl, float elapsedTime) {
	sf::Event event;
	if (ctrl.getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return true;

		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				ctrl.getStateMachine().Change("localmap");
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				_color += 79 % 255;
				_rect.setFillColor(sf::Color::Color(100, _color, 100));
			}
		}
	}
	return false;
}

void MainMenu::Render(sf::RenderWindow& window)
{
	window.draw(_rect);
}

void MainMenu::init()
{
	_rect.setPosition(0.f,0.f);
	_rect.setSize(sf::Vector2f(800.f, 600.f));
	_rect.setFillColor(sf::Color::Red);
}