#include "LocalMap.h"
#include "Controller.h"
#include <string>
#include "UserMovement.h"
#include "Utility.h"


#include "NPC.h"
#include "Dialog.h"
#include "IFScript.h"

LocalMap::LocalMap()
{
}

// handle events for localmap, check controls that has been pressed
bool LocalMap::handleEvents(const Control& controls)
{
	// set flag to change the state if the mouse has been pressed
	if (controls.isPressed(MOUSE_PRIMARY))
		_change_state.set();

	// controls to the scripts if there is one
	if (!_scripts.empty())
		_scripts.front()->handleEvents(controls);
	else // controls to the map
		_map->handleEvents(controls);

	return false;
}

// Update the localmap
void LocalMap::Update(Controller& ctrl, float elapsedTime)
{
	// if change state flag is set, stack game menu state
	if (_change_state)
		ctrl.getStateMachine().Stack("gamemenu"/*  ParamsCtrl(ctrl)*/);
	
	// update scripts if there is one
	if (!_scripts.empty())
	{
		if (_scripts.front()->hasEntered())
		{
			if (!_scripts.front()->Update(ctrl, elapsedTime))
				NextScript(ctrl);
		}
		else _scripts.front()->Enter(ctrl.getHero());
		
	}
	else // update map
		_map->Update(ctrl, *this, elapsedTime);
}

// render local map and scripts
void LocalMap::Render(Controller& ctrl)
{
	_map->Render(ctrl);
	if (!_scripts.empty())
		if (_scripts.front()->hasEntered())
			_scripts.front()->Render(ctrl);

}

// init local map
void LocalMap::init(StateParams* params)
{
	_map = shared_ptr<Map>(new Map("map.mp")); // create new map from map

	// add game objects to map
		
	_map->addGameObject(shared_ptr<GameObject>(new NPC(shared_ptr<Script>(new Dialog("hello!\ngoodbye...")),
		new Graphics(params->getCtrl().getHero().getHeroForMap()->getTexture(), sf::Vector2i(4,0), sf::Vector2u(64, 96)))),
		111);
	_map->addGameObject(shared_ptr<GameObject>(new NPC(shared_ptr<Script>(new Dialog("hello!\ngoodbye...")),
		new Graphics(params->getCtrl().getHero().getHeroForMap()->getTexture(), sf::Vector2i(4,0), sf::Vector2u(64, 96)))),
		111);
	_map->addGameObject(shared_ptr<GameObject>(new NPC(shared_ptr<Script>(new Dialog("I have a new chicken!")),
		new Graphics(params->getCtrl().getHero().getHeroForMap()->getTexture(), sf::Vector2i(4,4), sf::Vector2u(64, 96)))),
		57);
	_map->addGameObject(shared_ptr<GameObject>(new NPC(shared_ptr<Script>(new IFQItem("key", shared_ptr<Script>(new Dialog("You have the key.")), shared_ptr<Script>(new Dialog("You don't have the key.")))),
		new Graphics(params->getCtrl().getHero().getHeroForMap()->getTexture(), sf::Vector2i(6,0), sf::Vector2u(64, 96)))),
		315);

	// add hero to map
	_map->addGameObject(shared_ptr<GameObject>(params->getCtrl().getHero().getHeroForMap()), 21);
}

// add script to queue
void LocalMap::addScript(shared_ptr<Script>& script)
{
	_scripts.push(script);	
}

// change to next script
void LocalMap::NextScript(Controller& ctrl)
{
	// exit current
	_scripts.front()->Exit();
	_scripts.pop();
	// enter next
	if (!_scripts.empty())
		_scripts.front()->Enter(ctrl.getHero());
}