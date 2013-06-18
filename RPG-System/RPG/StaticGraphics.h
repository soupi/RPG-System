#pragma once

// graphics without animation

#include "Graphics.h"

class StaticGraphics : public Graphics
{
public:
	StaticGraphics(const sf::Texture* texture, sf::Vector2i loc_on_texture, const sf::Vector2u& size) : Graphics(texture, loc_on_texture, size) { }

	virtual void Update(float elapsedTime) { }
};