#include "Map.h"
#include <iostream>
#include "Utility.h"
#include "Controller.h"
#include <exception>
#include "Parser.h"

struct compare_obj_by_y
{
	bool operator() (const shared_ptr<GameObject> & lhs, const shared_ptr<GameObject> & rhs) { return lhs->getPos().y < rhs->getPos().y; }
};


Map::Map(string filename)
{
	loadMap(filename);
}

Map::~Map() { }

void Map::Update(Controller& ctrl, LocalMap& localmap, float elapsedTime)
{
	// update game objects
 
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
			(*obj)->Update(ctrl, localmap, elapsedTime);
	std::sort(_game_objects.begin(), _game_objects.end(), compare_obj_by_y());
}

void Map::handleEvents(const Control& controls)
{
	// game objects handle events

	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
		(*obj)->handleEvents(controls);
}

void Map::Render(Controller& ctrl)
{
	// draw background
	for (vector<Tile>::iterator tile = _background.begin(); tile != _background.end(); ++tile)
		tile->draw(ctrl.getWindow());
	// draw foreground
	for (vector<Tile>::iterator tile = _foreground.begin(); tile != _foreground.end(); ++tile)
		tile->draw(ctrl.getWindow());
	// draw game objects
	for (vector<shared_ptr<GameObject>>::iterator obj = _game_objects.begin(); obj != _game_objects.end(); ++obj)
		(*obj)->Render(ctrl);


	// draw top
	for (vector<Tile>::iterator tile = _top.begin(); tile != _top.end(); ++tile)
		tile->draw(ctrl.getWindow());
}

void Map::loadMap(string& filename)
{
	std::ifstream mapfile;
	mapfile.open("resources/maps/" + filename);

	if (!mapfile)
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
		
	mapfile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;

	// init
	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		_background.push_back(Tile());
		_foreground.push_back(Tile());
		_top.push_back(Tile());
	}

	loadLayer(mapfile, _background, _tileset_back);
	loadLayer(mapfile, _foreground, _tileset_fore);
	loadLayer(mapfile, _top, _tileset_top);

	Parser parser(mapfile);
	parser.Read(*this);

	mapfile.close();
}

void Map::loadLayer(std::ifstream& mapfile, vector<Tile>& layer, sf::Texture& tileset)
{
	unsigned size_w, size_h;
	mapfile >> size_w >> size_h;

	_width = size_w;

	mapfile.get();

	string tiles;
	getline(mapfile, tiles);

	loadTexture(tileset, "resources/" + tiles);

	for (unsigned i = 0; i < size_w*size_h; i++)
	{
		int tile;
		try {
			mapfile >> tile;
			if (tile)
			{
				layer[i] = Tile(&tileset, tile);
				layer[i].setPos(sf::Vector2f((i%size_w)*float(SCRN_TILE_SIZE), (i/size_w)*float(SCRN_TILE_SIZE)));
			}
		}
		catch (...) { }
	}
}

void Map::addGameObject(shared_ptr<GameObject>& obj, unsigned pos)
{
	if (pos > _background.size())
	{
		std::exception e("bad location for obj on map");
		throw(e);
	}
	int max = 0;

	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if (max < (*it)->getId())
			max = (*it)->getId();
	}

	obj->setId(max+1);

	obj->setPos(sf::Vector2f((pos%_width)*float(SCRN_TILE_SIZE) + obj->getRadius(), 
		(pos/_width)*float(SCRN_TILE_SIZE) + obj->getRadius()));

	_game_objects.push_back(obj);
	//std::sort(_game_objects.begin(), _game_objects.end(), compare_obj_by_y());

	for (int i = _game_objects.size() -1; 0 < i && _game_objects[i]->getPos().y < _game_objects[i-1]->getPos().y; --i)
		std::swap(_game_objects[i], _game_objects[i-1]);
}
void Map::addGameObject(shared_ptr<GameObject>& obj, const sf::Vector2f& pos)
{
	obj->setPos(pos);

	int max = 0;

	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if (max < (*it)->getId())
			max = (*it)->getId();

	}
	obj->setId(max+1);

	_game_objects.push_back(obj);
	

	//std::sort(_game_objects.begin(), _game_objects.end(), compare_obj_by_y());
	for (int i = _game_objects.size() -1; 0 < i && _game_objects[i]->getPos().y < _game_objects[i-1]->getPos().y; --i)
		std::swap(_game_objects[i], _game_objects[i-1]);
}


// ---------------- INTERACTIONS ----------------

bool Map::canStepOnFG(sf::Vector2f& pos) const
{
	sf::Vector2u my_pos(unsigned(pos.x)/SCRN_TILE_SIZE, unsigned(pos.y)/SCRN_TILE_SIZE);
	if (my_pos.x >= _width || my_pos.y >=  (_foreground.size() / _width)) // out of border
		return false;

	if (_foreground[my_pos.x + my_pos.y*_width].getNum())
		return false;

	return true;
}

bool Map::canStepOnFG(sf::Vector2f& pos, float radius) const
{
	
	if (!(canStepOnFG(sf::Vector2f(pos.x - radius, pos.y - radius)) && canStepOnFG(sf::Vector2f(pos.x - radius, pos.y +radius)) &&
		canStepOnFG(sf::Vector2f(pos.x + radius, pos.y - radius)) && canStepOnFG(sf::Vector2f(pos.x + radius, pos.y +radius))))
		return false;

	return true;
}

bool Map::canStepOnFG(sf::FloatRect& box) const
{
	
	if (!(canStepOnFG(sf::Vector2f(box.left, box.top)) && canStepOnFG(sf::Vector2f(box.left + box.width, box.top)) &&
		canStepOnFG(sf::Vector2f(box.left, box.top + box.height)) && canStepOnFG(sf::Vector2f(box.left + box.width, box.top + box.height))))
		return false;

	return true;
}

bool Map::canStepOn(GameObject& obj)
{
	sf::FloatRect box = obj.getCollisionBox();
	if (!canStepOnFG(box))
		return false;

	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if((it->get()) != &obj && (*it)->checkCollision(box) && !obj.canStepOn(*(it->get())))
			return false;
	}
	
	return true;
}

void Map::Step(LocalMap& localmap, GameObject& obj)
{
	sf::FloatRect box = obj.getCollisionBox();
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if((it->get()) != &obj && (*it)->checkCollision(box))
//			obj.StepOn(localmap, *(it->get())); // dispatch
			obj.StepOn(localmap, *(it->get())); // dispatch
	}
}

bool Map::Act(LocalMap& localmap, GameObject& obj, sf::FloatRect& box)
{
	bool acted = false;
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
		if((it->get()) != &obj && (*it)->checkCollision(box))
		{
		//	obj.act(localmap, *(it->get())); // dispatch
			(*it)->act(localmap, obj);
			acted = true;
		}
		return acted;
}

void Map::remGameObject(GameObject* obj)
{
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if ((*it).get() == obj)
		{
			_game_objects.erase(it);
			break;
		}
	}
}

const sf::Vector2f Map::getPosById(int id)
{
	for (vector<shared_ptr<GameObject>>::iterator it = _game_objects.begin(); it != _game_objects.end(); ++it)
	{
		if ((*it)->getId() == id)
			return (*it)->getPos();
	}
	return sf::Vector2f(0,0);
}