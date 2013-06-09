#include "UserMovement.h"
#include "Tile.h"
#include "LocalMap.h"
#include "GameObject.h"
#include "Utility.h"

// handle events. set direction from events
void UserMovement::handleEvents(const Control& controls)
{
	if (controls.isPressed(RIGHT))
		_dir.x = 1;
	else if (controls.isPressed(LEFT))
		_dir.x = -1;
	else _dir.x = 0;

	if (controls.isPressed(UP))
		_dir.y = -1;
	else if (controls.isPressed(DOWN))
		_dir.y = 1;
	else _dir.y = 0;

	// toggle run mode
	if (controls.isPressed(B))
		_run = true;
	else _run = false;
}

void UserMovement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	// set _direction with speed
	float scalar = 1.f;
	if (_run)
		scalar*=2.f;
	_direction = _dir*(scalar*float(_speed));
	// move
	Movement::Update(localmap, my_obj, my_graphics, elapsedTime);
}