#include "FollowIdMovement.h"
#include "Tile.h"
#include "LocalMap.h"
#include "GameObject.h"
#include "Utility.h"


void FollowIdMovement::handleEvents(const Control& controls)
{

}
// set new direction and move
void FollowIdMovement::Update(LocalMap& localmap, GameObject& my_obj, Graphics& my_graphics, float elapsedTime)
{
	if (!_newpos)
	{
		sf::Vector2f pos = my_obj.getPos();
		sf::Vector2f b_pos = localmap.getPosById(_id_to_follow);
		sf::Vector2f dir = localmap.getPosById(_id_to_follow) - my_obj.getPos();

		dir /= float(SCRN_TILE_SIZE);
		if (1.f < distance(dir, sf::Vector2f(0,0)) && distance(dir, sf::Vector2f(0,0)) < _radius)
		{
			if (dir.x)
				dir.x = abs(dir.x)/dir.x;
			if (dir.y)
				dir.y = abs(dir.y)/dir.y;
			_direction = dir;
		}
	
		else _direction = sf::Vector2f(0,0);
	}

	Movement::Update(localmap, my_obj, my_graphics, elapsedTime);
}