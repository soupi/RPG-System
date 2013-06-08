#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "HeroData.h"

using std::weak_ptr;

class HeroCharacter : public GameObject
{
public:
	HeroCharacter(shared_ptr<HeroData>& data);
	virtual void handleEvents(const Control& controls);
	virtual void Update(Controller& ctrl, LocalMap& localmap, float elapsedTime);
	sf::Texture* getTexture() { return &_hero_texture; }

	void act(LocalMap& localmap, GameObject& obj) { obj.act(localmap, *this); }
	void StepOn(LocalMap& localmap, GameObject& obj) { obj.StepOn(localmap, *this); }
	bool canStepOn(GameObject& obj) { return obj.canStepOn(*this); }

	void act(LocalMap& localmap, LocalObject& obj);
//	void act(LocalMap& localmap, Enemy& obj);
//	void StepOn(LocalMap& localmap, Enemy& obj);
//	bool canStepOn(Enemy& obj);

	void attack(Stats& stats);

	void giveQuestItem(QuestItem& item);
	bool hasQuestItem(const string& item_name);

private:
	sf::Texture _hero_texture;
	bool _act;
	float _clock;
	shared_ptr<HeroData> _hero_data;
	float _hurt_timer;
	bool _ishurt;
};