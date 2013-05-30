#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class HeroCharacter : public GameObject
{
public:
	HeroCharacter();
	virtual void handleEvents(const Control& controls);
	virtual sf::Vector2f Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	sf::Texture* getTexture() { return &_hero_texture; }

	void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

private:
	sf::Texture _hero_texture;
	bool _act;
};