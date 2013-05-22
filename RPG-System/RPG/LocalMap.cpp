#include "LocalMap.h"
#include "Controller.h"
#include <string>
#include "UserMovement.h"
#include "Utility.h"

LocalMap::LocalMap() 
{
	loadTexture(_hero_texture, "char.png");
}


bool LocalMap::handleEvents(const Control& controls)
{
	if (controls.isPressed(MOUSE_PRIMARY))
		_change_state.set();
			
	else if (controls.isPressed(MOUSE_SECONDARY))
		_color += 79 % 255;	

	_hero.handleEvents(controls);

	return false;
}
void LocalMap::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state)
		ctrl.getStateMachine().Stack("gamemenu");

	//_character.move(speed * _dir.x * elapsedTime, speed * _dir.y * elapsedTime);
	_hero.Update(ctrl, *this, elapsedTime);
	ctrl.getView().setCenter(_hero.getPos());
	//ctrl.getView().rotate(elapsedTime*45);

	_rect.setFillColor(sf::Color::Color(_color, 100, 100));
}



void LocalMap::Render(Controller& ctrl)
{
	_map->Render(ctrl);
	_hero.Render(ctrl);
}

void LocalMap::init()
{
	_rect.setPosition(0.f,0.f);
	_rect.setSize(sf::Vector2f(800.f, 600.f));
	_rect.setFillColor(sf::Color::Color(100, 100, 100));

	_character.setPosition(400.f,300.f);
	_character.setSize(sf::Vector2f(40.f, 40.f));
	_character.setFillColor(sf::Color::Color(60, 160, 250));
	_character.setOrigin(20.f, 20.f);

	_map = new Map("map.mp");

	_hero.setGraphics(new Graphics(&_hero_texture, sf::Vector2i(0,0), sf::Vector2u(64,96)));
	_hero.setMovement(new UserMovement);
}