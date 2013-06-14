#include "EyeFollowIdMovement.h"
#include "Utility.h"
#include "GameObject.h"

bool EyeFollowIdMovement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	setDir(localmap, my_obj);

	// if direction is zero stop and return.
	if (isZero(_direction))
		return false; 

	// set current graphical direction of movement
	my_graphics.setDir(_direction);
	my_obj.UpdateGraphics(elapsedTime);

	return false;
}