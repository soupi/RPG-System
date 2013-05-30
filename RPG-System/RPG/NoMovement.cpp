#include "NoMovement.h"
#include "GameObject.h"

sf::Vector2f NoMovement::Update(LocalMap& localmap, GameObject& my_obj, float elapsedTime) 
{
	if (_newpos)
	{
		my_obj.getGraphics()->setPos(_pos);

		_newpos = false;
	}
	return my_obj.getGraphics()->getPos();
}