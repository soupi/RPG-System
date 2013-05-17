#include "MainMenu.h"
#include "Controller.h"

bool MainMenu::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
		return true;

	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Right)
			_change_state.set();
			
		else if (event.mouseButton.button == sf::Mouse::Left)
			_color += 79 % 255;	
	}

	return false;
}
void MainMenu::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state)
		ctrl.getStateMachine().Stack("localmap");

	_rect.setFillColor(sf::Color::Color(_color, 100, 100));
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