#pragma once

// no graphics

#include "Macros.h"
#include "Graphics.h"

class NoGraphics : public Graphics
{
public:
	NoGraphics() { }
	virtual void Update() { }
	virtual void Render(sf::RenderWindow& window) { }
};