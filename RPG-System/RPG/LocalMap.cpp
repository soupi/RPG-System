#include "LocalMap.h"
#include "Controller.h"
#include <string>
#include "UserMovement.h"
#include "Utility.h"


#include "NPC.h"
#include "Dialog.h"

LocalMap::LocalMap()
{
}

bool LocalMap::handleEvents(const Control& controls)
{
	if (controls.isPressed(MOUSE_PRIMARY))
		_change_state.set();

	if (!_scripts.empty())
		_scripts.front()->handleEvents(controls);
	else 
		_map->handleEvents(controls);

	return false;
}
void LocalMap::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state)
		ctrl.getStateMachine().Stack("gamemenu"/*  ParamsCtrl(ctrl)*/);

	if (!_scripts.empty())
	{
		if (_scripts.front()->hasEntered())
		{
			if (!_scripts.front()->Update(ctrl, elapsedTime))
				NextScript(ctrl);
		}
		else _scripts.front()->Enter(ctrl.getHero());
		
	}
	else
		_map->Update(ctrl, *this, elapsedTime);
}

void LocalMap::Render(Controller& ctrl)
{
	_map->Render(ctrl);
	if (!_scripts.empty())
		if (_scripts.front()->hasEntered())
			_scripts.front()->Render(ctrl);

}

void LocalMap::init(StateParams* params)
{
	_map = shared_ptr<Map>(new Map("map.mp"));

	_map->addGameObject(shared_ptr<GameObject>(params->getCtrl().getHero().getHeroForMap()), 21);
	_map->addGameObject(shared_ptr<GameObject>(new NPC(shared_ptr<Script>(new Dialog("hello!")),
		new Graphics(params->getCtrl().getHero().getHeroForMap()->getTexture(), sf::Vector2i(1,0), sf::Vector2u(64, 96)))),
		111);
}

void LocalMap::addScript(shared_ptr<Script>& script)
{
	_scripts.push(script);	
}

void LocalMap::NextScript(Controller& ctrl)
{
	_scripts.front()->Exit();
	_scripts.pop();
	if (!_scripts.empty())
		_scripts.front()->Enter(ctrl.getHero());
}