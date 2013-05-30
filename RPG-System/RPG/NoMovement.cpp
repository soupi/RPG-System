#include "NoMovement.h"
#include "GameObject.h"

void NoMovement::Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime) 
{
	if (_newpos)
	{
		my_obj.getGraphics()->setPos(_init_pos);

		_newpos = false;
	}
}