#include "LocalMap.h"
#include "Controller.h"
#include <string>
#include "UserMovement.h"
#include "Utility.h"

#include "Enemy.h"
#include "ParamsCtrl.h"

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
	if (!_scripts.empty() && _scripts.front()->hasEntered())
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
		ctrl.getStateMachine().Stack("gamemenu", shared_ptr<StateParams>(new ParamsCtrl(ctrl)));
	
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
	ctrl.getHero().getHeroData()->showHP(ctrl);
	if (!_scripts.empty())
		if (_scripts.front()->hasEntered())
			_scripts.front()->Render(ctrl);

}

// init local map
void LocalMap::init(shared_ptr<StateParams>& params)
{
	unsigned starting_tile = 0;
	try {
		ParamsMap* params_map = (ParamsMap*)(params.get());
		_map = shared_ptr<Map>(new Map(params_map->getMap())); // create new map from map
		starting_tile = params_map->StartingTile();
	}
	catch (...)
	{
		std::cerr << "No Map";
		exit(EXIT_FAILURE);
	}
	// add game objects to map
		
	// add hero to map
	_map->addGameObject(shared_ptr<GameObject>(params->getCtrl().getHero().getHeroForMap()), starting_tile);
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