#include "DirMovement.h"
#include "Utility.h"
#include "GameObject.h"
#include "LocalMap.h"

// set new direction and move
bool DirMovement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	_direction = _dir;

	// if direction is zero stop and return.
	if (isZero(_direction))
		return false; 

	// set current graphical direction of movement
	my_graphics.setDir(_direction);
	my_obj.UpdateGraphics(elapsedTime);

	sf::Vector2f last = my_obj.getPos();

	// try moving
	sf::Vector2f temp_dir = _speed * _direction  * elapsedTime;
	my_graphics.move(temp_dir);

	// check if move is valid
	if (!localmap.canStepOn(my_obj))
		return false;

	localmap.Step(my_obj);

	return !(last == my_obj.getPos());
}