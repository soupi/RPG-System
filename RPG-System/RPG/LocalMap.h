#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "StateParams.h"
#include "Flag.h"
#include "Map.h"


const float speed = 250.f;

class LocalMap : public State
{
public:
	virtual State* Enter(StateParams* params = NULL) { init(); return this; }
	virtual bool handleEvents(sf::Event& event);
	virtual void Update(Controller& ctrl, float elapsedTime);
	virtual void Render(sf::RenderWindow& window);

private:
	sf::RectangleShape _rect;
	sf::RectangleShape _character;

	Flag _change_state;
	sf::Vector2f _dir;

	char _color;
	void init();

	Map* _map;
};