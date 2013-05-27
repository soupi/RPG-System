#pragma once

#include "HeroCharacter.h"
#include "UserMovement.h"
#include "Utility.h"
#include "Controller.h"

HeroCharacter::HeroCharacter()
{
	loadTexture(_hero_texture, "char.png");
	GameObject::setGraphics(new Graphics(&_hero_texture, sf::Vector2i(0,0), sf::Vector2u(64,96)));
	GameObject::setMovement(new UserMovement);
}

void HeroCharacter::handleEvents(const Control& controls)
{
	GameObject::handleEvents(controls);
}
sf::Vector2f HeroCharacter::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{

	GameObject::Update(ctrl, localmap, elapsedTime);
	// draw Lives and HP
	ctrl.getView().setCenter(getPos());
	return getPos();
}
void HeroCharacter::StepOn(LocalMap& localmap, GameObject& obj)
{
	
}
bool HeroCharacter::canStepOn(GameObject& obj)
{
	return true;
}