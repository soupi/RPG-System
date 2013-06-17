#pragma once

#include <SFML\Graphics.hpp>

class Controller;

enum FADE_TYPE {
	FADE_IN = 1,
	FADE_OUT = 2,
	NONE = 0,
};

class Fade
{
public:
	void fadeIn();
	void fadeOut();
	void update(Controller& ctrl, float elapsedTime);
	void render(Controller& ctrl);
	bool isFading() const { return (_fade_type != NONE); }

private:
	sf::RectangleShape _rect;
	FADE_TYPE _fade_type;
	int _alpha;
};