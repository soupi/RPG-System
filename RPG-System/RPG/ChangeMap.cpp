#include "ChangeMap.h"

// Updated the state
bool ChangeMap::Update(Controller& ctrl, float elapsedTime) 
{
	// fade out of current map
	if (_fade.isFading())
		_fade.update(ctrl, elapsedTime);
	// if we are done fading, change the map.
	else {
		ctrl.getStateMachine().Change("localmap", shared_ptr<StateParams>(new ParamsMap(ctrl, _map_name, _loc)));
		_continue = false;
	}
	return _continue;
} 