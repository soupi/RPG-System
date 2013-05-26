#include "LocalMap.h"
#include "Controller.h"
#include <string>
#include "UserMovement.h"
#include "Utility.h"

LocalMap::LocalMap()
{
}

bool LocalMap::handleEvents(const Control& controls)
{
	if (controls.isPressed(MOUSE_PRIMARY))
		_change_state.set();
	_map->handleEvents(controls);

	return false;
}
void LocalMap::Update(Controller& ctrl, float elapsedTime)
{
	if (_change_state)
		ctrl.getStateMachine().Stack("gamemenu"/*  ParamsCtrl(ctrl)*/);
	_map->Update(ctrl, *this, elapsedTime);
}

void LocalMap::Render(Controller& ctrl)
{
	_map->Render(ctrl);
}

void LocalMap::init(StateParams* params)
{
	_map = shared_ptr<Map>(new Map("map.mp"));

	_map->addGameObject(shared_ptr<GameObject>(params->getCtrl().getHero().getHeroForMap()), 1);
}