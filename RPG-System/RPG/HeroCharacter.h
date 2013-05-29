#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class HeroCharacter : public GameObject
{
public:
	HeroCharacter();
	virtual void handleEvents(const Control& controls);
	virtual sf::Vector2f Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	virtual void StepOn(LocalMap& localmap, GameObject& obj);
	virtual bool canStepOn(GameObject& obj);
	sf::Texture* getTexture() { return &_hero_texture; }
private:
	sf::Texture _hero_texture;
};