#include "NoMovement.h"
#include "GameObject.h"

void NoMovement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime) 
{
	if (_newpos)
	{
		my_graphics.setPos(_init_pos);

		_newpos = false;
	}
}