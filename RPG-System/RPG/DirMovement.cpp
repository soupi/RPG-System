#include "DirMovement.h"

// set new direction and move
void DirMovement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	_direction = _dir;

	Movement::Update(localmap, my_obj, my_graphics, elapsedTime);
}