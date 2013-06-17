#include "LocalMap.h"
#include "Controller.h"
#include <string>
#include "UserMovement.h"
#include "Utility.h"

#include "Enemy.h"
#include "ParamsCtrl.h"
#include "ParamsMap.h"

LocalMap::LocalMap()
{
}

// handle events for localmap, check controls that has been pressed
bool LocalMap::handleEvents(const Control& controls)
{
	// set flag to change the state if the mouse has been pressed
	if (controls.isPressed(PAUSE) || controls.isPressed(ESC))
		_change_state.set();

	// controls to the scripts if there is one
	if (!_scripts.empty() && _scripts.front()->hasEntered())
		_scripts.front()->handleEvents(controls);
	else // controls to the map
	{
		if (!_commands.empty() && _commands.front()->hasEntered())
			_commands.front()->handleEvents(controls);
		_map->handleEvents(controls);
	}

	return false;
}

// Update the localmap
void LocalMap::Update(Controller& ctrl, float elapsedTime)
{
	if (_fade.isFading())
		_fade.update(ctrl, elapsedTime);

	_first_update = true;
	// if change state flag is set, stack game menu state
	if (_change_state)
		ctrl.getStateMachine().Stack("pause", shared_ptr<StateParams>(new ParamsCtrl(ctrl)));
	
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
	{
		if (!_commands.empty())
		{
			if (_commands.front()->hasEntered())
			{
				if (!_commands.front()->Update(ctrl, elapsedTime))
					NextCommand(ctrl);
			}
			else {
				_commands.front()->Enter(ctrl.getHero());
				if (!_commands.front()->Update(ctrl, elapsedTime))
					NextCommand(ctrl);
			}
		
		}

		_map->Update(ctrl, *this, elapsedTime);
	}
}

// render local map and scripts
void LocalMap::Render(Controller& ctrl)
{
	if (!_first_update)
		return;
	_map->Render(ctrl);
	ctrl.getHero().getHeroData()->showHP(ctrl);
	if (!_scripts.empty())
		if (_scripts.front()->hasEntered())
			_scripts.front()->Render(ctrl);

	if (!_commands.empty())
		if (_commands.front()->hasEntered())
			_commands.front()->Render(ctrl);

//	if (_fade.isFading())
	//	_fade.render(ctrl);
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
	_fade.fadeIn();
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

// add commad to queue
void LocalMap::addCommand(shared_ptr<Script>& script)
{
	_commands.push(script);
}

// change to next command
void LocalMap::NextCommand(Controller& ctrl)
{
	// exit current
	_commands.front()->Exit();
	_commands.pop();
	// enter next
	if (!_commands.empty())
		_commands.front()->Enter(ctrl.getHero());
}